from langchain.llms.base import LLM
from typing import Any, List, Optional
from langchain.callbacks.manager import CallbackManagerForLLMRun
from transformers import AutoTokenizer, AutoModelForCausalLM
import torch

from langchain.document_loaders import UnstructuredFileLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain.document_loaders import PyMuPDFLoader
from langchain.document_loaders.word_document import Docx2txtLoader
from langchain.vectorstores import Chroma
from langchain.embeddings.huggingface import HuggingFaceEmbeddings
from tqdm import tqdm
import os

from langchain.chains.summarize import load_summarize_chain
from langchain.prompts import PromptTemplate
from langchain.chains import RetrievalQA


class InternLM(LLM):
    # 基于本地 InternLM 自定义 LLM 类
    tokenizer : AutoTokenizer = None
    model: AutoModelForCausalLM = None
    
    def __init__(self, model_path: str):
        # model_path: InternLM 模型路径
        # 从本地初始化模型
        super().__init__()
        print("正在从本地加载模型...")
        self.tokenizer = AutoTokenizer.from_pretrained(model_path, trust_remote_code=True)
        self.model = AutoModelForCausalLM.from_pretrained(model_path, trust_remote_code=True).to(torch.bfloat16).cuda()
        self.model = self.model.eval()
        print("完成本地模型的加载")

    def _call(self, prompt: str, stop: Optional[List[str]] = None,
                run_manager: Optional[CallbackManagerForLLMRun] = None,
                **kwargs: Any):
        # 重写调用函数
        response, history = self.model.chat(self.tokenizer, prompt , history=[])
        return response
        
    @property
    def _llm_type(self) -> str:
        return "InternLM"
    
    
class Reading_Comprehension:
    # 实现阅读理解板块
    
    def __init__(self, dir_path: str, embed_path: str, model_path: str, db_path: str):
        """
        参数:
        - dir_path：目标文件夹路径
        - embed_path：Embedding 模型路径
        - model_path：LLM 模型路径
        - db_path：向量数据库持久化路径
        """
        self.dir_path = dir_path
        self.embed_path = embed_path
        self.model_path = model_path
        self.db_path = db_path
        

    def get_texts(self, dir_path: str) -> list:
        """
        解析目标文件夹路径下能够处理的文件（目前只支持 pdf/word/txt）
        
        参数：
        - dir_path：目标文件夹路径
        
        返回：
        - docs：由每一页的解析内容构成的列表
        """
        file_list = []
        for filepath, dirnames, filenames in os.walk(dir_path):
            # os.walk 函数将递归遍历指定文件夹
            for filename in filenames:
                # 通过后缀名判断文件类型是否满足要求
                if filename.endswith(".pdf"):
                    # 如果满足要求，将其绝对路径加入到结果列表
                    file_list.append(os.path.join(filepath, filename))
                elif filename.endswith(".docx"):
                    file_list.append(os.path.join(filepath, filename))
                elif filename.endswith(".txt"):
                    file_list.append(os.path.join(filepath, filename))
                    
        # docs 存放加载之后的纯文本对象
        docs = []
        # 遍历所有目标文件
        for one_file in tqdm(file_list):
            file_type = one_file.split('.')[-1]
            if file_type == 'pdf':
                loader = PyMuPDFLoader(one_file)
            elif file_type == 'docx':
                loader = Docx2txtLoader(one_file)
            elif file_type == 'txt':
                loader = UnstructuredFileLoader(one_file)
            else:
                # 如果是不符合条件的文件，直接跳过
                continue
            docs.extend(loader.load())
        return docs

    
    def text_split(self, docs: list) -> list:
        """
        对文本进行分块
        
        参数：
        - docs：需要分块的文本内容
        
        返回：
        - split_docs：分块后的文本构成的列表
        """
        text_splitter = RecursiveCharacterTextSplitter(
            chunk_size=1000, chunk_overlap=150)
        split_docs = text_splitter.split_documents(docs)
        return split_docs
    
    def load_model(self):
        """
        加载模型
        
        返回：
        embed_model：Embedding 模型
        llm：LLM 模型
        """
        embed_model = HuggingFaceEmbeddings(model_name=self.embed_path)
        llm = InternLM(model_path=self.model_path)
        return embed_model, llm
    
    
    def creat_db(self, split_docs: list, embed_model):
        """
        构建向量数据库
        
        参数：
        - spilit_docs：分块后的文本内容
        - embed_model：Embedding 模型
        """
        # 加载数据库
        vectordb = Chroma.from_documents(
            documents=split_docs,
            embedding=embed_model,
            persist_directory=self.db_path  # 将persist_directory目录保存到磁盘上
        )
        # 将加载的向量数据库持久化到磁盘上
        vectordb.persist()
        print("完成向量数据库的搭建")
        return

        
    def generation_summary(self, docs: list, llm) -> str:
        """
        生成摘要。
        
        参数：
        - docs (list): 包含文档内容的字符串列表。
        - llm: LLM 模型，用于生成摘要。

        返回
        - output_summary：生成的摘要。
        """
        chain = load_summarize_chain(llm, chain_type="refine")
        output_summary = chain.run(docs)
        print("完成摘要生成")
        return output_summary
    
    
    def generation_qa(self, embed_model, llm, summary) -> str:
        """
        生成五个基于文章的问题和对应的答案
        
        参数：
        - embed_model：Embedding 模型
        - llm：LLM 模型
        - summary：文章的摘要
        
        返回：
        - result['result']：生成的问题和答案
        """
        # 加载数据库
        vectordb = Chroma(
            persist_directory=self.db_path,  # 允许我们将persist_directory目录保存到磁盘上
            embedding_function=embed_model
        )
        
        template = """You are an assistant for question-answering tasks. Use the following pieces of retrieved context to answer the question. If you don't know the answer, just say that you don't know. Use three sentences maximum and keep the answer concise.
        Question: {question} 
        Context: {context} 
        Answer:"""
        qa_chain_prompt = PromptTemplate(input_variables=["context","question"],template=template)
        qa_chain = RetrievalQA.from_chain_type(llm,retriever=vectordb.as_retriever(),return_source_documents=True,chain_type_kwargs={"prompt":qa_chain_prompt})
        
        question = """You are a good teacher of reading comprehension. Please ask five reading comprehension questions and answer them based on the context.
        Question:What is the main content of this book?
        Answer:{summary}
        Question:
        Answer:"""  
        result = qa_chain({"query": question})
        print("完成问答对生成")
        return result["result"]
    
    
    def workflow(self) -> dict:
        """
        执行整个工作流程：解析文件内容、存储到向量数据库、生成文章摘要、生成基于文章的问答对
        
        返回：
        - dicts：一个包含了 摘要 和 问答对 的字典
        """
        docs = self.get_texts(self.dir_path)
        split_docs = self.text_split(docs)
        embed_model, llm = self.load_model()
        self.creat_db(split_docs, embed_model)
        summary = self.generation_summary(docs, llm)
        qa_pairs = self.generation_qa(embed_model, llm, summary)
        dicts = {}
        dicts['摘要'] = summary
        dicts['问答对'] = qa_pairs
        print('done')
        return dicts
    

if __name__ == "__main__":
    my_test = Reading_Comprehension(dir_path='/root/autodl-tmp/yuedu/data',
                                embed_path='/root/autodl-tmp/embedding_model',
                                model_path='/root/autodl-tmp/Shanghai_AI_Laboratory/internlm2-chat-7b',
                                db_path='/root/autudl-tmp/data_base/vector_db/chroma')
    dicts = my_test.workflow()
    # dicts.to_json('/root/autodl-tmp/result.json', orient="records")
    print(dicts)
        

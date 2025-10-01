import cv2
import numpy as np
import os
from PIL import Image, ImageTk
import tkinter as tk
from tkinter import filedialog, ttk, messagebox
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import time
from image_hash import ImageHash

class ImageSimilarityApp:
    """图像相似度检测系统GUI应用"""
    
    def __init__(self, root):
        self.root = root
        self.root.title("基于感知哈希算法的图像相似度检测系统")
        self.root.geometry("1200x800")
        self.root.configure(bg="#f0f0f0")
        
        # 设置中文字体
        plt.rcParams["font.family"] = ["Microsoft YaHei", "SimHei", "Arial"]
        
        # 图像路径
        self.image1_path = ""
        self.image2_path = ""
        self.image_dir = ""
        self.image_paths = []
        
        # 创建界面
        self._create_widgets()
        
        # 结果数据
        self.results = []
        
    def _create_widgets(self):
        """创建GUI组件"""
        # 创建主框架
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.pack(fill=tk.BOTH, expand=True)
        
        # 左侧控制面板
        control_frame = ttk.LabelFrame(main_frame, text="控制面板", padding="10")
        control_frame.pack(side=tk.LEFT, fill=tk.Y, padx=5, pady=5)
        
        # 图像选择区域
        ttk.Label(control_frame, text="图像选择:").pack(anchor=tk.W, pady=5)
        
        ttk.Button(control_frame, text="选择第一张图像", 
                  command=self._select_image1).pack(fill=tk.X, pady=2)
        
        ttk.Button(control_frame, text="选择第二张图像", 
                  command=self._select_image2).pack(fill=tk.X, pady=2)
        
        ttk.Button(control_frame, text="选择图像文件夹", 
                  command=self._select_image_dir).pack(fill=tk.X, pady=2)
        
        # 算法选择区域
        ttk.Label(control_frame, text="算法选择:").pack(anchor=tk.W, pady=5)
        
        self.algorithm_var = tk.StringVar(value="pHash")
        algorithms = ["pHash", "dHash", "SSIM", "直方图"]
        
        for algo in algorithms:
            ttk.Radiobutton(control_frame, text=algo, 
                          variable=self.algorithm_var, 
                          value=algo).pack(anchor=tk.W)
        
        # 阈值设置
        ttk.Label(control_frame, text="相似度阈值:").pack(anchor=tk.W, pady=5)
        
        self.threshold_var = tk.DoubleVar(value=0.8)
        threshold_frame = ttk.Frame(control_frame)
        threshold_frame.pack(fill=tk.X)
        
        ttk.Scale(threshold_frame, variable=self.threshold_var, 
                 from_=0.0, to=1.0, orient=tk.HORIZONTAL,
                 command=lambda v: self._update_threshold_label(float(v))).pack(side=tk.LEFT, fill=tk.X, expand=True)
        
        self.threshold_label = ttk.Label(threshold_frame, text="0.80")
        self.threshold_label.pack(side=tk.RIGHT, padx=5)
        
        # 操作按钮
        ttk.Button(control_frame, text="比较两张图像", 
                  command=self._compare_two_images).pack(fill=tk.X, pady=10)
        
        ttk.Button(control_frame, text="批量比较图像", 
                  command=self._batch_compare_images).pack(fill=tk.X, pady=2)
        
        ttk.Button(control_frame, text="算法对比实验", 
                  command=self._run_algorithm_comparison).pack(fill=tk.X, pady=2)
        
        ttk.Button(control_frame, text="保存结果", 
                  command=self._save_results).pack(fill=tk.X, pady=2)
        
        # 右侧显示区域
        display_frame = ttk.Frame(main_frame)
        display_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=5, pady=5)
        
        # 图像显示区域
        image_frame = ttk.LabelFrame(display_frame, text="图像显示", padding="10")
        image_frame.pack(fill=tk.BOTH, expand=True, pady=5)
        
        # 图像1显示
        self.image1_label = ttk.Label(image_frame, text="请选择第一张图像")
        self.image1_label.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5)
        
        # 图像2显示
        self.image2_label = ttk.Label(image_frame, text="请选择第二张图像")
        self.image2_label.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True, padx=5)
        
        # 结果显示区域
        result_frame = ttk.LabelFrame(display_frame, text="结果分析", padding="10")
        result_frame.pack(fill=tk.BOTH, expand=True, pady=5)
        
        # 结果文本
        self.result_text = tk.Text(result_frame, height=6, wrap=tk.WORD)
        self.result_text.pack(fill=tk.BOTH, expand=True, pady=5)
        self.result_text.config(state=tk.DISABLED)
        
        # 图表显示
        self.chart_frame = ttk.Frame(result_frame)
        self.chart_frame.pack(fill=tk.BOTH, expand=True)
        
        # 状态栏
        self.status_var = tk.StringVar(value="就绪")
        status_bar = ttk.Label(self.root, textvariable=self.status_var, relief=tk.SUNKEN, anchor=tk.W)
        status_bar.pack(side=tk.BOTTOM, fill=tk.X)
    
    def _update_threshold_label(self, value):
        """更新阈值标签显示"""
        self.threshold_label.config(text=f"{value:.2f}")
    
    def _select_image1(self):
        """选择第一张图像"""
        path = filedialog.askopenfilename(
            filetypes=[("图像文件", "*.jpg;*.jpeg;*.png;*.bmp;*.gif")]
        )
        if path:
            self.image1_path = path
            self._display_image(path, self.image1_label)
            self.status_var.set(f"已选择第一张图像: {os.path.basename(path)}")
    
    def _select_image2(self):
        """选择第二张图像"""
        path = filedialog.askopenfilename(
            filetypes=[("图像文件", "*.jpg;*.jpeg;*.png;*.bmp;*.gif")]
        )
        if path:
            self.image2_path = path
            self._display_image(path, self.image2_label)
            self.status_var.set(f"已选择第二张图像: {os.path.basename(path)}")
    
    def _select_image_dir(self):
        """选择图像文件夹"""
        dir_path = filedialog.askdirectory()
        if dir_path:
            self.image_dir = dir_path
            # 获取文件夹中所有图像文件
            image_extensions = ['.jpg', '.jpeg', '.png', '.bmp', '.gif']
            self.image_paths = [
                os.path.join(dir_path, f) for f in os.listdir(dir_path)
                if os.path.isfile(os.path.join(dir_path, f)) and 
                os.path.splitext(f)[1].lower() in image_extensions
            ]
            self.status_var.set(f"已选择图像文件夹，包含 {len(self.image_paths)} 张图像")
    
    def _display_image(self, image_path, label):
        """在标签中显示图像"""
        try:
            # 打开图像并调整大小以适应显示
            img = Image.open(image_path)
            img.thumbnail((400, 400))  # 限制最大尺寸
            photo = ImageTk.PhotoImage(img)
            
            # 更新标签
            label.config(image=photo)
            label.image = photo  # 保持引用
            label.text = ""  # 清除文本
        except Exception as e:
            messagebox.showerror("错误", f"无法显示图像: {str(e)}")
            self.status_var.set(f"显示图像错误: {str(e)}")
    
    def _compare_two_images(self):
        """比较两张图像的相似度"""
        if not self.image1_path or not self.image2_path:
            messagebox.showwarning("警告", "请先选择两张图像")
            return
        
        self.status_var.set("正在计算相似度...")
        self.root.update()
        
        try:
            algorithm = self.algorithm_var.get()
            start_time = time.time()
            
            if algorithm == "pHash":
                hash1 = ImageHash.phash(self.image1_path)
                hash2 = ImageHash.phash(self.image2_path)
                distance = ImageHash.hamming_distance(hash1, hash2)
                # 将汉明距离转换为相似度 (0-64 -> 1-0)
                similarity = 1 - (distance / 64)
                result_text = f"pHash 汉明距离: {distance}\n相似度: {similarity:.4f}"
                
            elif algorithm == "dHash":
                hash1 = ImageHash.dhash(self.image1_path)
                hash2 = ImageHash.dhash(self.image2_path)
                distance = ImageHash.hamming_distance(hash1, hash2)
                # 将汉明距离转换为相似度 (0-64 -> 1-0)
                similarity = 1 - (distance / 64)
                result_text = f"dHash 汉明距离: {distance}\n相似度: {similarity:.4f}"
                
            elif algorithm == "SSIM":
                ssim_value = ImageHash.ssim(self.image1_path, self.image2_path)
                similarity = ssim_value
                result_text = f"SSIM 值: {ssim_value:.4f}"
                
            elif algorithm == "直方图":
                hist_sim = ImageHash.histogram_similarity(self.image1_path, self.image2_path)
                similarity = hist_sim
                result_text = f"直方图相似度: {hist_sim:.4f}"
            
            # 判断是否相似
            threshold = self.threshold_var.get()
            if similarity >= threshold:
                result_text += "\n结论: 两图像相似"
            else:
                result_text += "\n结论: 两图像不相似"
                
            # 计算耗时
            elapsed_time = (time.time() - start_time) * 1000
            result_text += f"\n计算耗时: {elapsed_time:.2f} 毫秒"
            
            # 显示结果
            self.result_text.config(state=tk.NORMAL)
            self.result_text.delete(1.0, tk.END)
            self.result_text.insert(tk.END, result_text)
            self.result_text.config(state=tk.DISABLED)
            
            # 保存结果
            self.results.append({
                "image1": os.path.basename(self.image1_path),
                "image2": os.path.basename(self.image2_path),
                "algorithm": algorithm,
                "similarity": similarity,
                "time": elapsed_time
            })
            
            # 更新图表
            self._update_chart()
            
            self.status_var.set("相似度计算完成")
            
        except Exception as e:
            messagebox.showerror("错误", f"计算相似度时出错: {str(e)}")
            self.status_var.set(f"计算错误: {str(e)}")
    
    def _batch_compare_images(self):
        """批量比较文件夹中的图像"""
        if not self.image_dir or len(self.image_paths) < 2:
            messagebox.showwarning("警告", "请先选择包含至少两张图像的文件夹")
            return
        
        self.status_var.set("正在批量比较图像...")
        self.root.update()
        
        try:
            algorithm = self.algorithm_var.get()
            threshold = self.threshold_var.get()
            result_text = f"批量比较结果 ({algorithm}):\n\n"
            similar_pairs = 0
            total_pairs = 0
            start_time = time.time()
            
            # 比较所有图像对
            for i in range(len(self.image_paths)):
                for j in range(i + 1, len(self.image_paths)):
                    total_pairs += 1
                    img1 = self.image_paths[i]
                    img2 = self.image_paths[j]
                    
                    if algorithm == "pHash":
                        hash1 = ImageHash.phash(img1)
                        hash2 = ImageHash.phash(img2)
                        distance = ImageHash.hamming_distance(hash1, hash2)
                        similarity = 1 - (distance / 64)
                        
                    elif algorithm == "dHash":
                        hash1 = ImageHash.dhash(img1)
                        hash2 = ImageHash.dhash(img2)
                        distance = ImageHash.hamming_distance(hash1, hash2)
                        similarity = 1 - (distance / 64)
                        
                    elif algorithm == "SSIM":
                        similarity = ImageHash.ssim(img1, img2)
                        
                    elif algorithm == "直方图":
                        similarity = ImageHash.histogram_similarity(img1, img2)
                    
                    # 记录相似的图像对
                    if similarity >= threshold:
                        similar_pairs += 1
                        img1_name = os.path.basename(img1)
                        img2_name = os.path.basename(img2)
                        result_text += f"{img1_name} 与 {img2_name}: {similarity:.4f}\n"
                        
                    # 更新进度
                    if total_pairs % 10 == 0:
                        self.status_var.set(f"已比较 {total_pairs} 对图像")
                        self.root.update()
            
            # 计算总耗时
            elapsed_time = (time.time() - start_time) * 1000
            result_text += f"\n总比较对数: {total_pairs}"
            result_text += f"\n相似图像对: {similar_pairs}"
            result_text += f"\n总耗时: {elapsed_time:.2f} 毫秒"
            result_text += f"\n平均每对耗时: {elapsed_time/total_pairs:.2f} 毫秒"
            
            # 显示结果
            self.result_text.config(state=tk.NORMAL)
            self.result_text.delete(1.0, tk.END)
            self.result_text.insert(tk.END, result_text)
            self.result_text.config(state=tk.DISABLED)
            
            # 更新图表
            self._update_batch_chart(algorithm, total_pairs, similar_pairs, elapsed_time)
            
            self.status_var.set(f"批量比较完成，共比较 {total_pairs} 对图像")
            
        except Exception as e:
            messagebox.showerror("错误", f"批量比较时出错: {str(e)}")
            self.status_var.set(f"批量比较错误: {str(e)}")
    
    def _run_algorithm_comparison(self):
        """运行不同算法的对比实验"""
        if not self.image1_path or not self.image2_path:
            messagebox.showwarning("警告", "请先选择两张图像进行对比实验")
            return
        
        self.status_var.set("正在进行算法对比实验...")
        self.root.update()
        
        try:
            result_text = "算法对比实验结果:\n\n"
            algorithms = ["pHash", "dHash", "SSIM", "直方图"]
            similarities = []
            times = []
            
            for algo in algorithms:
                start_time = time.time()
                
                if algo == "pHash":
                    hash1 = ImageHash.phash(self.image1_path)
                    hash2 = ImageHash.phash(self.image2_path)
                    distance = ImageHash.hamming_distance(hash1, hash2)
                    similarity = 1 - (distance / 64)
                    
                elif algo == "dHash":
                    hash1 = ImageHash.dhash(self.image1_path)
                    hash2 = ImageHash.dhash(self.image2_path)
                    distance = ImageHash.hamming_distance(hash1, hash2)
                    similarity = 1 - (distance / 64)
                    
                elif algo == "SSIM":
                    similarity = ImageHash.ssim(self.image1_path, self.image2_path)
                    
                elif algo == "直方图":
                    similarity = ImageHash.histogram_similarity(self.image1_path, self.image2_path)
                
                # 计算耗时
                elapsed_time = (time.time() - start_time) * 1000
                
                similarities.append(similarity)
                times.append(elapsed_time)
                
                result_text += f"{algo}: 相似度 = {similarity:.4f}, 耗时 = {elapsed_time:.2f} 毫秒\n"
            
            # 显示结果
            self.result_text.config(state=tk.NORMAL)
            self.result_text.delete(1.0, tk.END)
            self.result_text.insert(tk.END, result_text)
            self.result_text.config(state=tk.DISABLED)
            
            # 更新对比图表
            self._update_comparison_chart(algorithms, similarities, times)
            
            self.status_var.set("算法对比实验完成")
            
        except Exception as e:
            messagebox.showerror("错误", f"算法对比实验出错: {str(e)}")
            self.status_var.set(f"对比实验错误: {str(e)}")
    
    def _update_chart(self):
        """更新结果图表"""
        # 清除现有图表
        for widget in self.chart_frame.winfo_children():
            widget.destroy()
        
        if not self.results:
            return
        
        # 获取最新结果
        latest = self.results[-1]
        
        # 创建图表
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 3))
        fig.tight_layout(pad=3.0)
        
        # 相似度条形图
        ax1.bar([latest["algorithm"]], [latest["similarity"]], color='skyblue')
        ax1.set_ylim(0, 1)
        ax1.set_title("相似度")
        ax1.text(0, latest["similarity"] + 0.05, f"{latest['similarity']:.4f}", 
                ha='center', va='bottom')
        
        # 耗时条形图
        ax2.bar([latest["algorithm"]], [latest["time"]], color='lightgreen')
        ax2.set_title("耗时 (毫秒)")
        ax2.text(0, latest["time"] + 0.5, f"{latest['time']:.2f}ms", 
                ha='center', va='bottom')
        
        # 在Tkinter中显示图表
        canvas = FigureCanvasTkAgg(fig, master=self.chart_frame)
        canvas.draw()
        canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
    
    def _update_batch_chart(self, algorithm, total, similar, time):
        """更新批量比较图表"""
        # 清除现有图表
        for widget in self.chart_frame.winfo_children():
            widget.destroy()
        
        # 创建图表
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 3))
        fig.tight_layout(pad=3.0)
        
        # 相似比例饼图
        ax1.pie([similar, total - similar], labels=['相似', '不相似'], 
                autopct='%1.1f%%', colors=['lightgreen', 'lightcoral'])
        ax1.set_title(f'相似比例 ({algorithm})')
        
        # 性能指标
        ax2.bar(['总耗时 (ms)', '平均每对耗时 (ms)'], [time, time/total], 
                color=['skyblue', 'orange'])
        ax2.set_title('性能指标')
        
        # 在Tkinter中显示图表
        canvas = FigureCanvasTkAgg(fig, master=self.chart_frame)
        canvas.draw()
        canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
    
    def _update_comparison_chart(self, algorithms, similarities, times):
        """更新算法对比图表"""
        # 清除现有图表
        for widget in self.chart_frame.winfo_children():
            widget.destroy()
        
        # 创建图表
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 3))
        fig.tight_layout(pad=3.0)
        
        # 相似度对比
        x = range(len(algorithms))
        ax1.bar(x, similarities, color='skyblue')
        ax1.set_xticks(x)
        ax1.set_xticklabels(algorithms, rotation=45)
        ax1.set_ylim(0, 1)
        ax1.set_title("算法相似度对比")
        
        # 耗时对比
        ax2.bar(x, times, color='lightgreen')
        ax2.set_xticks(x)
        ax2.set_xticklabels(algorithms, rotation=45)
        ax2.set_title("算法耗时对比 (毫秒)")
        
        # 在Tkinter中显示图表
        canvas = FigureCanvasTkAgg(fig, master=self.chart_frame)
        canvas.draw()
        canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
    
    def _save_results(self):
        """保存结果到文件"""
        if not self.results:
            messagebox.showwarning("警告", "没有可保存的结果")
            return
        
        try:
            # 询问保存路径
            save_path = filedialog.asksaveasfilename(
                defaultextension=".txt",
                filetypes=[("文本文件", "*.txt"), ("所有文件", "*.*")]
            )
            
            if not save_path:
                return
            
            # 写入结果
            with open(save_path, "w", encoding="utf-8") as f:
                f.write("图像相似度检测结果\n")
                f.write("====================\n\n")
                
                for i, result in enumerate(self.results, 1):
                    f.write(f"结果 {i}:\n")
                    f.write(f"  图像1: {result['image1']}\n")
                    f.write(f"  图像2: {result['image2']}\n")
                    f.write(f"  算法: {result['algorithm']}\n")
                    f.write(f"  相似度: {result['similarity']:.4f}\n")
                    f.write(f"  耗时: {result['time']:.2f} 毫秒\n\n")
            
            messagebox.showinfo("成功", f"结果已保存到:\n{save_path}")
            self.status_var.set(f"结果已保存到 {os.path.basename(save_path)}")
            
        except Exception as e:
            messagebox.showerror("错误", f"保存结果时出错: {str(e)}")
            self.status_var.set(f"保存错误: {str(e)}")

if __name__ == "__main__":
    root = tk.Tk()
    app = ImageSimilarityApp(root)
    root.mainloop()

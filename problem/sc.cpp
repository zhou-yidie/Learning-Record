/*
3
23 96 36 
这一份源码是生成这样的n个数 
*/ 
 
#include <iostream>  
#include <fstream>  
#include <random>  
#include <vector>  
#include <ctime>

using namespace std;  
  
int main() {  
    // 初始化随机数生成器  
    
    // 生成n的值，这里我们假设n在1到100之间(包含1和100) 
    uniform_int_distribution<> dis_n(1, 100);  
    for(int i=1;i<=1;i++)//要生成多少组测试点这里就改到几 
    {
        //int n = dis_n(gen);  
        // random_device rd;  
        // mt19937 gen(rd());  
        int n = 397;
        // 生成n个随机数的分布，这里我们假设每个数在1到1000之间  
        //gen(rd()); 
        //random_device time;
        mt19937 gen(time(nullptr));
        // ; 
        
        // mt19937 gen(rd());
        uniform_int_distribution<> dis_num(1, 10000);  
        
        // 创建一个vector来存储n个随机数  
        vector<int> numbers(n);  
        
        // 生成n个随机数并存储在vector中  
        for (int i = 0; i < n; ++i) {  
            numbers[i] = dis_num(gen);  
        }  
        
        // 构造文件名  
        string filename = to_string(i) + ".in"; // 你可以根据需要更改文件名生成规则  
    
        // 打开文件准备写入  
        ofstream outFile(filename);  
    
        if (!outFile.is_open()) {  
            cerr << "无法打开文件 " << filename << " 进行写入" << endl;  
            return 1; // 返回一个错误码  
        }  
        outFile<<n<<endl;//打印出n
        // 将n个随机数写入文件  
        /*for (int num : numbers) {  
                outFile << num << " "; // 将每个数写入文件，并在数之间加上空格  
            }  */
        for(int i=0;i<n;i++)
        {
            outFile << 0 << " ";
            //outFile <<numbers[i]<<" "; 
        }
    
        // 如果不需要在文件末尾有空格，可以添加一个换行符或者不在循环内添加空格  
        outFile << endl; // 在文件末尾添加一个换行符  
    
        // 关闭文件  
        outFile.close();  
    
        cout << "n的值是 " << n << "，随机生成的数已成功写入 " << filename << " 文件" << endl;  
    }
    return 0;  
}
 
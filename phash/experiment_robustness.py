import cv2
import numpy as np
import os
import shutil
import matplotlib.pyplot as plt
from image_hash import ImageHash
import time

class RobustnessTester:
    """图像哈希算法鲁棒性测试类"""
    
    def __init__(self, test_image_path, output_dir="robustness_tests"):
        """
        初始化鲁棒性测试器
        :param test_image_path: 测试图像路径
        :param output_dir: 输出测试结果的目录
        """
        self.test_image_path = test_image_path
        self.image_name = os.path.splitext(os.path.basename(test_image_path))[0]
        self.output_dir = output_dir
        
        # 创建输出目录
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        
        # 读取原始图像
        self.original_image = cv2.imread(test_image_path)
        if self.original_image is None:
            raise Exception(f"无法读取测试图像: {test_image_path}")
        
        # 保存原始图像
        self.original_path = os.path.join(output_dir, f"{self.image_name}_original.jpg")
        cv2.imwrite(self.original_path, self.original_image)
        
        # 测试结果
        self.results = {
            "pHash": [],
            "dHash": [],
            "SSIM": [],
            "直方图": []
        }
        
        # 测试参数
        self.parameters = {
            "压缩质量": [100, 90, 80, 70, 60, 50, 40, 30, 20, 10],
            "缩放比例": [2.0, 1.5, 1.2, 0.8, 0.5, 0.3],
            "旋转角度": [-15, -10, -5, 5, 10, 15],
            "亮度调整": [-50, -30, -20, -10, 10, 20, 30, 50]
        }
        
        # 设置中文字体
        plt.rcParams["font.family"] = ["Microsoft YaHei", "SimHei", "Arial"]
    
    def _apply_jpeg_compression(self, quality):
        """
        应用JPEG压缩
        :param quality: 压缩质量 (0-100)
        :return: 处理后的图像路径
        """
        output_path = os.path.join(self.output_dir, f"{self.image_name}_compressed_q{quality}.jpg")
        cv2.imwrite(output_path, self.original_image, [int(cv2.IMWRITE_JPEG_QUALITY), quality])
        return output_path
    
    def _apply_scaling(self, scale):
        """
        应用缩放
        :param scale: 缩放比例
        :return: 处理后的图像路径
        """
        height, width = self.original_image.shape[:2]
        new_size = (int(width * scale), int(height * scale))
        scaled_image = cv2.resize(self.original_image, new_size, interpolation=cv2.INTER_AREA)
        
        # 再缩放回原始大小以便比较
        scaled_back_image = cv2.resize(scaled_image, (width, height), interpolation=cv2.INTER_AREA)
        
        output_path = os.path.join(self.output_dir, f"{self.image_name}_scaled_{scale:.1f}.jpg")
        cv2.imwrite(output_path, scaled_back_image)
        return output_path
    
    def _apply_rotation(self, angle):
        """
        应用旋转
        :param angle: 旋转角度
        :return: 处理后的图像路径
        """
        height, width = self.original_image.shape[:2]
        center = (width // 2, height // 2)
        
        # 计算旋转矩阵
        rotation_matrix = cv2.getRotationMatrix2D(center, angle, 1.0)
        
        # 计算旋转后的图像大小
        cos = np.abs(rotation_matrix[0, 0])
        sin = np.abs(rotation_matrix[0, 1])
        new_width = int((height * sin) + (width * cos))
        new_height = int((height * cos) + (width * sin))
        
        # 调整旋转矩阵以防止裁剪
        rotation_matrix[0, 2] += (new_width / 2) - center[0]
        rotation_matrix[1, 2] += (new_height / 2) - center[1]
        
        # 应用旋转
        rotated_image = cv2.warpAffine(
            self.original_image, 
            rotation_matrix, 
            (new_width, new_height),
            borderMode=cv2.BORDER_CONSTANT,
            borderValue=(255, 255, 255)  # 白色背景
        )
        
        # 缩放回原始大小
        rotated_scaled_image = cv2.resize(rotated_image, (width, height), interpolation=cv2.INTER_AREA)
        
        output_path = os.path.join(self.output_dir, f"{self.image_name}_rotated_{angle}deg.jpg")
        cv2.imwrite(output_path, rotated_scaled_image)
        return output_path
    
    def _apply_brightness_change(self, value):
        """
        应用亮度变化
        :param value: 亮度变化值 (负值变暗，正值变亮)
        :return: 处理后的图像路径
        """
        # 转换为HSV色彩空间以便调整亮度
        hsv_image = cv2.cvtColor(self.original_image, cv2.COLOR_BGR2HSV)
        h, s, v = cv2.split(hsv_image)
        
        # 调整亮度
        v = cv2.add(v, value)
        v = np.clip(v, 0, 255)  # 确保值在有效范围内
        
        # 合并通道并转换回BGR
        adjusted_hsv = cv2.merge((h, s, v))
        adjusted_image = cv2.cvtColor(adjusted_hsv, cv2.COLOR_HSV2BGR)
        
        output_path = os.path.join(self.output_dir, f"{self.image_name}_brightness_{value}.jpg")
        cv2.imwrite(output_path, adjusted_image)
        return output_path
    
    def run_tests(self):
        """运行所有鲁棒性测试"""
        print(f"开始对图像 '{self.image_name}' 进行鲁棒性测试...")
        
        # 计算原始图像的哈希值
        original_phash = ImageHash.phash(self.original_path)
        original_dhash = ImageHash.dhash(self.original_path)
        
        # 对每种变换类型进行测试
        for transform_type, params in self.parameters.items():
            print(f"  正在测试 {transform_type}...")
            
            for param in params:
                # 应用变换
                if transform_type == "压缩质量":
                    transformed_path = self._apply_jpeg_compression(param)
                elif transform_type == "缩放比例":
                    transformed_path = self._apply_scaling(param)
                elif transform_type == "旋转角度":
                    transformed_path = self._apply_rotation(param)
                elif transform_type == "亮度调整":
                    transformed_path = self._apply_brightness_change(param)
                
                # 计算各种算法的相似度
                # pHash
                transformed_phash = ImageHash.phash(transformed_path)
                phash_distance = ImageHash.hamming_distance(original_phash, transformed_phash)
                phash_similarity = 1 - (phash_distance / 64)
                
                # dHash
                transformed_dhash = ImageHash.dhash(transformed_path)
                dhash_distance = ImageHash.hamming_distance(original_dhash, transformed_dhash)
                dhash_similarity = 1 - (dhash_distance / 64)
                
                # SSIM
                ssim_value = ImageHash.ssim(self.original_path, transformed_path)
                
                # 直方图
                hist_sim = ImageHash.histogram_similarity(self.original_path, transformed_path)
                
                # 保存结果
                self.results["pHash"].append({
                    "transform": transform_type,
                    "parameter": param,
                    "similarity": phash_similarity
                })
                
                self.results["dHash"].append({
                    "transform": transform_type,
                    "parameter": param,
                    "similarity": dhash_similarity
                })
                
                self.results["SSIM"].append({
                    "transform": transform_type,
                    "parameter": param,
                    "similarity": ssim_value
                })
                
                self.results["直方图"].append({
                    "transform": transform_type,
                    "parameter": param,
                    "similarity": hist_sim
                })
        
        print("鲁棒性测试完成!")
        self.generate_report()
    
    def generate_report(self):
        """生成测试报告和图表"""
        # 创建报告目录
        report_dir = os.path.join(self.output_dir, "report")
        if not os.path.exists(report_dir):
            os.makedirs(report_dir)
        
        # 1. 为每种变换类型创建单独的图表
        for transform_type in self.parameters.keys():
            fig, ax = plt.subplots(figsize=(12, 8))
            
            # 为每种算法绘制曲线
            colors = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4']
            markers = ['o', 's', '^', 'D']
            
            for i, algorithm in enumerate(self.results.keys()):
                # 筛选该变换类型的结果
                transform_results = [
                    res for res in self.results[algorithm]
                    if res["transform"] == transform_type
                ]
                
                # 按参数排序
                transform_results.sort(key=lambda x: x["parameter"])
                
                # 提取参数和相似度
                parameters = [res["parameter"] for res in transform_results]
                similarities = [res["similarity"] for res in transform_results]
                
                # 绘制曲线
                ax.plot(parameters, similarities, marker=markers[i], 
                       color=colors[i], linewidth=2.5, markersize=8,
                       label=algorithm, alpha=0.8)
            
            ax.set_title(f"{transform_type}对算法鲁棒性的影响", fontsize=16, fontweight='bold', pad=20)
            ax.set_xlabel(transform_type, fontsize=14)
            ax.set_ylabel("相似度", fontsize=14)
            ax.set_ylim(0, 1.05)
            ax.grid(True, linestyle='--', alpha=0.7)
            ax.legend(fontsize=12, loc='best')
            
            # 设置坐标轴
            ax.tick_params(axis='both', which='major', labelsize=12)
            
            # 保存图表
            plot_path = os.path.join(report_dir, f"{transform_type}_comparison.png")
            plt.tight_layout()
            plt.savefig(plot_path, dpi=300, bbox_inches='tight')
            plt.close()
        
        # 2. 创建综合对比图表（所有变换类型在一个图中）
        self._create_comprehensive_chart(report_dir)
        
        # 3. 创建算法性能热力图
        self._create_heatmap(report_dir)
        
        # 4. 创建算法鲁棒性雷达图
        self._create_radar_chart(report_dir)
        
        # 生成文本报告
        report_path = os.path.join(report_dir, "robustness_report.txt")
        with open(report_path, "w", encoding="utf-8") as f:
            f.write("图像哈希算法鲁棒性测试报告\n")
            f.write("=============================\n\n")
            f.write(f"测试图像: {self.test_image_path}\n")
            f.write(f"测试日期: {time.strftime('%Y-%m-%d %H:%M:%S')}\n\n")
            
            for transform_type in self.parameters.keys():
                f.write(f"【{transform_type}测试】\n")
                f.write("-" * 40 + "\n")
                
                # 提取该变换类型的所有参数
                params = sorted(self.parameters[transform_type])
                
                # 写入表头
                f.write(f"{'参数':<10}")
                for algorithm in self.results.keys():
                    f.write(f"{algorithm:<12}")
                f.write("\n")
                
                # 写入结果
                for param in params:
                    f.write(f"{param:<10}")
                    for algorithm in self.results.keys():
                        # 查找对应结果
                        for res in self.results[algorithm]:
                            if res["transform"] == transform_type and res["parameter"] == param:
                                f.write(f"{res['similarity']:.4f}    ")
                                break
                    f.write("\n")
                f.write("\n")
        
        print(f"测试报告已生成在: {report_dir}")
    
    def _create_comprehensive_chart(self, report_dir):
        """创建综合对比图表（所有变换类型在一个图中）"""
        fig, axes = plt.subplots(2, 2, figsize=(16, 12))
        fig.suptitle('图像哈希算法鲁棒性综合对比', fontsize=18, fontweight='bold', y=0.95)
        
        colors = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4']
        markers = ['o', 's', '^', 'D']
        
        transform_types = list(self.parameters.keys())
        
        for idx, transform_type in enumerate(transform_types):
            row = idx // 2
            col = idx % 2
            ax = axes[row, col]
            
            # 为每种算法绘制曲线
            for i, algorithm in enumerate(self.results.keys()):
                # 筛选该变换类型的结果
                transform_results = [
                    res for res in self.results[algorithm]
                    if res["transform"] == transform_type
                ]
                
                # 按参数排序
                transform_results.sort(key=lambda x: x["parameter"])
                
                # 提取参数和相似度
                parameters = [res["parameter"] for res in transform_results]
                similarities = [res["similarity"] for res in transform_results]
                
                # 绘制曲线
                ax.plot(parameters, similarities, marker=markers[i], 
                       color=colors[i], linewidth=2.5, markersize=6,
                       label=algorithm, alpha=0.8)
            
            ax.set_title(f"{transform_type}", fontsize=14, fontweight='bold')
            ax.set_xlabel(transform_type, fontsize=12)
            ax.set_ylabel("相似度", fontsize=12)
            ax.set_ylim(0, 1.05)
            ax.grid(True, linestyle='--', alpha=0.7)
            ax.legend(fontsize=10)
            ax.tick_params(axis='both', which='major', labelsize=10)
        
        plt.tight_layout()
        plot_path = os.path.join(report_dir, "comprehensive_comparison.png")
        plt.savefig(plot_path, dpi=300, bbox_inches='tight')
        plt.close()
    
    def _create_heatmap(self, report_dir):
        """创建算法性能热力图"""
        # 准备数据矩阵
        algorithms = list(self.results.keys())
        transform_types = list(self.parameters.keys())
        
        # 计算每种算法在每种变换下的平均相似度
        heatmap_data = np.zeros((len(algorithms), len(transform_types)))
        
        for i, algorithm in enumerate(algorithms):
            for j, transform_type in enumerate(transform_types):
                # 获取该算法在该变换类型下的所有相似度
                similarities = [
                    res["similarity"] for res in self.results[algorithm]
                    if res["transform"] == transform_type
                ]
                # 计算平均相似度
                heatmap_data[i, j] = np.mean(similarities) if similarities else 0
        
        # 创建热力图
        fig, ax = plt.subplots(figsize=(10, 6))
        
        # 绘制热力图
        im = ax.imshow(heatmap_data, cmap='RdYlGn', aspect='auto', vmin=0, vmax=1)
        
        # 设置标签
        ax.set_xticks(range(len(transform_types)))
        ax.set_yticks(range(len(algorithms)))
        ax.set_xticklabels(transform_types, fontsize=12)
        ax.set_yticklabels(algorithms, fontsize=12)
        
        # 添加数值标注
        for i in range(len(algorithms)):
            for j in range(len(transform_types)):
                text = ax.text(j, i, f'{heatmap_data[i, j]:.3f}',
                             ha="center", va="center", color="black", fontsize=10)
        
        # 设置标题和标签
        ax.set_title('算法鲁棒性热力图（平均相似度）', fontsize=16, fontweight='bold', pad=20)
        ax.set_xlabel('变换类型', fontsize=14)
        ax.set_ylabel('算法', fontsize=14)
        
        # 添加颜色条
        cbar = plt.colorbar(im, ax=ax)
        cbar.set_label('相似度', fontsize=12)
        
        plt.tight_layout()
        plot_path = os.path.join(report_dir, "robustness_heatmap.png")
        plt.savefig(plot_path, dpi=300, bbox_inches='tight')
        plt.close()
    
    def _create_radar_chart(self, report_dir):
        """创建算法鲁棒性雷达图"""
        # 准备数据
        algorithms = list(self.results.keys())
        transform_types = list(self.parameters.keys())
        
        # 计算每种算法在每种变换下的平均相似度
        radar_data = {}
        for algorithm in algorithms:
            radar_data[algorithm] = []
            for transform_type in transform_types:
                similarities = [
                    res["similarity"] for res in self.results[algorithm]
                    if res["transform"] == transform_type
                ]
                avg_similarity = np.mean(similarities) if similarities else 0
                radar_data[algorithm].append(avg_similarity)
        
        # 设置雷达图
        angles = np.linspace(0, 2 * np.pi, len(transform_types), endpoint=False).tolist()
        angles += angles[:1]  # 闭合图形
        
        fig, ax = plt.subplots(figsize=(10, 10), subplot_kw=dict(projection='polar'))
        
        colors = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4']
        
        for i, algorithm in enumerate(algorithms):
            values = radar_data[algorithm] + radar_data[algorithm][:1]  # 闭合图形
            ax.plot(angles, values, 'o-', linewidth=2, label=algorithm, color=colors[i])
            ax.fill(angles, values, alpha=0.25, color=colors[i])
        
        # 设置标签
        ax.set_xticks(angles[:-1])
        ax.set_xticklabels(transform_types, fontsize=12)
        ax.set_ylim(0, 1)
        ax.set_yticks([0.2, 0.4, 0.6, 0.8, 1.0])
        ax.set_yticklabels(['0.2', '0.4', '0.6', '0.8', '1.0'], fontsize=10)
        ax.grid(True)
        
        # 设置标题和图例
        ax.set_title('算法鲁棒性雷达图', fontsize=16, fontweight='bold', pad=30)
        ax.legend(loc='upper right', bbox_to_anchor=(1.3, 1.0), fontsize=12)
        
        plt.tight_layout()
        plot_path = os.path.join(report_dir, "robustness_radar.png")
        plt.savefig(plot_path, dpi=300, bbox_inches='tight')
        plt.close()

if __name__ == "__main__":
    # 示例用法
    import sys
    
    if len(sys.argv) > 1:
        test_image = sys.argv[1]
    else:
        # 如果没有提供图像路径，使用示例图像
        test_image = "test_image.jpg"  # 请替换为实际的测试图像路径
    
    if not os.path.exists(test_image):
        print(f"错误: 找不到测试图像 {test_image}")
        sys.exit(1)
    
    # 创建测试器并运行测试
    tester = RobustnessTester(test_image)
    tester.run_tests()

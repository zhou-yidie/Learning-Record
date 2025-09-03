#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
基于感知哈希算法的图像相似度检测与对比分析
Perceptual Hash Algorithm for Image Similarity Detection and Comparison

支持的哈希算法：
1. 平均哈希 (Average Hash) - aHash
2. 感知哈希 (Perceptual Hash) - pHash  
3. 差异哈希 (Difference Hash) - dHash
4. 小波哈希 (Wavelet Hash) - wHash

作者: yidiezhou
日期: 2024
"""

import cv2
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from typing import Tuple, List, Union
import os
import time


class PerceptualHash:
    """感知哈希算法类"""
    
    def __init__(self, hash_size: int = 64):
        """
        初始化感知哈希算法
        
        Args:
            hash_size: 哈希值的大小，默认为64x64 (4096位)
        """
        self.hash_size = hash_size
        self.hash_length = hash_size * hash_size
        
    def _resize_image(self, image: np.ndarray) -> np.ndarray:
        """将图像调整为指定大小"""
        return cv2.resize(image, (self.hash_size, self.hash_size))
    
    def _rgb_to_grayscale(self, image: np.ndarray) -> np.ndarray:
        """将RGB图像转换为灰度图像"""
        if len(image.shape) == 3:
            return cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
        return image
    
    def average_hash(self, image: np.ndarray) -> str:
        """
        平均哈希算法 (aHash)
        
        算法步骤：
        1. 将图像缩放为64x64
        2. 转换为灰度图
        3. 计算像素平均值
        4. 将每个像素与平均值比较，大于平均值为1，否则为0
        5. 生成4096位二进制哈希值
        """
        # 调整图像大小
        resized = self._resize_image(image)
        # 转换为灰度图
        gray = self._rgb_to_grayscale(resized)
        # 计算平均值
        mean = np.mean(gray)
        # 生成哈希值
        hash_value = (gray > mean).flatten()
        # 转换为十六进制字符串
        return ''.join(['1' if x else '0' for x in hash_value])
    
    def perceptual_hash(self, image: np.ndarray) -> str:
        """
        感知哈希算法 (pHash)
        
        算法步骤：
        1. 将图像缩放为128x128
        2. 转换为灰度图
        3. 应用离散余弦变换(DCT)
        4. 取DCT系数的左上角64x64部分
        5. 计算DCT系数的平均值
        6. 将每个系数与平均值比较，大于平均值为1，否则为0
        7. 生成4096位二进制哈希值
        """
        # 调整图像大小为128x128以获得更好的DCT效果
        resized = cv2.resize(image, (128, 128))
        # 转换为灰度图
        gray = self._rgb_to_grayscale(resized)
        # 应用DCT变换
        dct = cv2.dct(np.float32(gray))
        # 取左上角64x64的DCT系数
        dct_low = dct[:self.hash_size, :self.hash_size]
        # 计算平均值
        mean = np.mean(dct_low)
        # 生成哈希值
        hash_value = (dct_low > mean).flatten()
        # 转换为二进制字符串
        return ''.join(['1' if x else '0' for x in hash_value])
    
    def difference_hash(self, image: np.ndarray) -> str:
        """
        差异哈希算法 (dHash)
        
        算法步骤：
        1. 将图像缩放为65x64（为了计算差值）
        2. 转换为灰度图
        3. 计算相邻像素的差值
        4. 差值大于0为1，否则为0
        5. 生成4096位二进制哈希值
        """
        # 调整图像大小为65x64（为了计算差值）
        resized = cv2.resize(image, (self.hash_size + 1, self.hash_size))
        # 转换为灰度图
        gray = self._rgb_to_grayscale(resized)
        # 计算差值
        diff = gray[:, 1:] > gray[:, :-1]
        # 生成哈希值
        hash_value = diff.flatten()
        # 转换为二进制字符串
        return ''.join(['1' if x else '0' for x in hash_value])
    
    def wavelet_hash(self, image: np.ndarray) -> str:
        """
        小波哈希算法 (wHash)
        
        算法步骤：
        1. 将图像缩放为128x128
        2. 转换为灰度图
        3. 应用小波变换
        4. 取低频部分
        5. 计算平均值并生成哈希值
        """
        try:
            import pywt
            # 调整图像大小
            resized = cv2.resize(image, (128, 128))
            # 转换为灰度图
            gray = self._rgb_to_grayscale(resized)
            
            # 应用小波变换
            coeffs = pywt.wavedec2(gray, 'haar', level=1)
            # 取低频部分
            cA = coeffs[0]
            # 调整大小
            cA_resized = cv2.resize(cA, (self.hash_size, self.hash_size))
            # 计算平均值
            mean = np.mean(cA_resized)
            # 生成哈希值
            hash_value = (cA_resized > mean).flatten()
            # 转换为二进制字符串
            return ''.join(['1' if x else '0' for x in hash_value])
        except ImportError:
            # 如果没有pywt库，使用改进的感知哈希作为替代
            return self._enhanced_perceptual_hash(image)
    
    def _enhanced_perceptual_hash(self, image: np.ndarray) -> str:
        """
        增强感知哈希算法 (作为小波哈希的替代)
        
        算法步骤：
        1. 将图像缩放为128x128
        2. 转换为灰度图
        3. 应用高斯模糊减少噪声
        4. 应用DCT变换
        5. 取低频部分并生成哈希值
        """
        # 调整图像大小为128x128
        resized = cv2.resize(image, (128, 128))
        # 转换为灰度图
        gray = self._rgb_to_grayscale(resized)
        
        # 应用高斯模糊减少噪声
        blurred = cv2.GaussianBlur(gray, (3, 3), 0)
        
        # 应用DCT变换
        dct = cv2.dct(np.float32(blurred))
        # 取左上角64x64的DCT系数
        dct_low = dct[:self.hash_size, :self.hash_size]
        
        # 计算平均值
        mean = np.mean(dct_low)
        # 生成哈希值
        hash_value = (dct_low > mean).flatten()
        # 转换为二进制字符串
        return ''.join(['1' if x else '0' for x in hash_value])
    
    def calculate_hamming_distance(self, hash1: str, hash2: str) -> int:
        """
        计算两个哈希值之间的汉明距离
        
        Args:
            hash1: 第一个哈希值
            hash2: 第二个哈希值
            
        Returns:
            汉明距离（不同位的数量）
        """
        if len(hash1) != len(hash2):
            raise ValueError("哈希值长度必须相同")
        
        return sum(c1 != c2 for c1, c2 in zip(hash1, hash2))
    
    def calculate_similarity(self, hash1: str, hash2: str) -> float:
        """
        计算两个哈希值之间的相似度
        
        Args:
            hash1: 第一个哈希值
            hash2: 第二个哈希值
            
        Returns:
            相似度百分比 (0-100)
        """
        distance = self.calculate_hamming_distance(hash1, hash2)
        max_distance = len(hash1)
        similarity = (max_distance - distance) / max_distance * 100
        return similarity
    
    def get_all_hashes(self, image: np.ndarray) -> dict:
        """
        获取图像的所有哈希值
        
        Args:
            image: 输入图像
            
        Returns:
            包含所有哈希值的字典
        """
        return {
            'aHash': self.average_hash(image),
            'pHash': self.perceptual_hash(image),
            'dHash': self.difference_hash(image),
            'wHash': self.wavelet_hash(image)
        }


class ImageSimilarityAnalyzer:
    """图像相似度分析器"""
    
    def __init__(self, hash_size: int = 64):
        """
        初始化图像相似度分析器
        
        Args:
            hash_size: 哈希值的大小，默认为64x64 (4096位)
        """
        self.hasher = PerceptualHash(hash_size)
        
    def load_image(self, image_path: str) -> np.ndarray:
        """
        加载图像
        
        Args:
            image_path: 图像文件路径
            
        Returns:
            图像数组
        """
        if not os.path.exists(image_path):
            raise FileNotFoundError(f"图像文件不存在: {image_path}")
        
        # 使用OpenCV加载图像（保持BGR格式，因为哈希算法在BGR上更准确）
        image = cv2.imread(image_path)
        if image is None:
            raise ValueError(f"无法加载图像: {image_path}")
        
        return image
    
    def compare_images(self, image1_path: str, image2_path: str) -> dict:
        """
        比较两个图像的相似度
        
        Args:
            image1_path: 第一个图像路径
            image2_path: 第二个图像路径
            
        Returns:
            包含相似度信息的字典
        """
        # 加载图像
        image1 = self.load_image(image1_path)
        image2 = self.load_image(image2_path)
        
        # 计算哈希值
        hashes1 = self.hasher.get_all_hashes(image1)
        hashes2 = self.hasher.get_all_hashes(image2)
        
        # 计算相似度
        results = {}
        for hash_type in hashes1.keys():
            distance = self.hasher.calculate_hamming_distance(
                hashes1[hash_type], hashes2[hash_type]
            )
            similarity = self.hasher.calculate_similarity(
                hashes1[hash_type], hashes2[hash_type]
            )
            
            results[hash_type] = {
                'hash1': hashes1[hash_type],
                'hash2': hashes2[hash_type],
                'distance': distance,
                'similarity': similarity
            }
        
        return {
            'image1_path': image1_path,
            'image2_path': image2_path,
            'results': results,
            'images': [image1, image2]
        }
    
    def batch_compare(self, image_paths: List[str]) -> List[dict]:
        """
        批量比较多个图像
        
        Args:
            image_paths: 图像路径列表
            
        Returns:
            比较结果列表
        """
        if len(image_paths) < 2:
            raise ValueError("至少需要2张图像进行比较")
        
        results = []
        for i in range(len(image_paths)):
            for j in range(i + 1, len(image_paths)):
                try:
                    result = self.compare_images(image_paths[i], image_paths[j])
                    results.append(result)
                except Exception as e:
                    print(f"比较图像 {image_paths[i]} 和 {image_paths[j]} 时出错: {e}")
        
        return results
    
    def find_similar_images(self, target_image_path: str, 
                           candidate_image_paths: List[str], 
                           threshold: float = 80.0) -> List[dict]:
        """
        在候选图像中查找与目标图像相似的图像
        
        Args:
            target_image_path: 目标图像路径
            candidate_image_paths: 候选图像路径列表
            threshold: 相似度阈值 (0-100)
            
        Returns:
            相似图像列表
        """
        target_image = self.load_image(target_image_path)
        target_hashes = self.hasher.get_all_hashes(target_image)
        
        similar_images = []
        
        for candidate_path in candidate_image_paths:
            try:
                candidate_image = self.load_image(candidate_path)
                candidate_hashes = self.hasher.get_all_hashes(candidate_image)
                
                # 计算平均相似度
                similarities = []
                for hash_type in target_hashes.keys():
                    similarity = self.hasher.calculate_similarity(
                        target_hashes[hash_type], 
                        candidate_hashes[hash_type]
                    )
                    similarities.append(similarity)
                
                avg_similarity = np.mean(similarities)
                
                if avg_similarity >= threshold:
                    similar_images.append({
                        'path': candidate_path,
                        'similarity': avg_similarity,
                        'details': {
                            'aHash': similarities[0],
                            'pHash': similarities[1],
                            'dHash': similarities[2],
                            'wHash': similarities[3]
                        }
                    })
                    
            except Exception as e:
                print(f"处理图像 {candidate_path} 时出错: {e}")
        
        # 按相似度排序
        similar_images.sort(key=lambda x: x['similarity'], reverse=True)
        return similar_images
    
    def visualize_comparison(self, comparison_result, save_path=None):
        """
        可视化比较结果
        Visualize comparison results
        """
        try:
            import matplotlib.pyplot as plt
            import matplotlib.font_manager as fm
            
            # 设置中文字体支持
            plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'DejaVu Sans']
            plt.rcParams['axes.unicode_minus'] = False
            
            # 创建图表
            fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(15, 5))
            
            # 显示第一张图像（BGR转RGB用于显示）
            ax1.imshow(cv2.cvtColor(comparison_result['images'][0], cv2.COLOR_BGR2RGB))
            ax1.set_title(f"Image 1: {os.path.basename(comparison_result['image1_path'])}")
            ax1.axis('off')
            
            # 显示第二张图像（BGR转RGB用于显示）
            ax2.imshow(cv2.cvtColor(comparison_result['images'][1], cv2.COLOR_BGR2RGB))
            ax2.set_title(f"Image 2: {os.path.basename(comparison_result['image2_path'])}")
            ax2.axis('off')
            
            # Display similarity results
            hash_types = list(comparison_result['results'].keys())
            similarities = [comparison_result['results'][ht]['similarity'] for ht in hash_types]
            
            bars = ax3.bar(hash_types, similarities, color=['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4'])
            ax3.set_title('Similarity Results')
            ax3.set_ylabel('Similarity (%)')
            ax3.set_ylim(0, 100)
            
            # Add value labels on bars
            for bar, similarity in zip(bars, similarities):
                height = bar.get_height()
                ax3.text(bar.get_x() + bar.get_width()/2., height + 1,
                        f'{similarity:.1f}%', ha='center', va='bottom')
            
            # Rotate x-axis labels
            ax3.tick_params(axis='x', rotation=45)
            
            plt.tight_layout()
            
            if save_path:
                plt.savefig(save_path, dpi=300, bbox_inches='tight')
                print(f"Visualization saved to: {save_path}")
            
            plt.show()
            
        except ImportError:
            print("Matplotlib not available. Cannot generate visualization.")
        except Exception as e:
            print(f"Error generating visualization: {e}")


def main():
    """主函数 - 演示用法"""
    print("=== 基于感知哈希算法的图像相似度检测与对比分析 ===\n")
    
    # 创建分析器
    analyzer = ImageSimilarityAnalyzer()
    
    # 示例用法
    print("1. 创建分析器实例")
    print("2. 加载图像")
    print("3. 计算哈希值")
    print("4. 比较相似度")
    print("5. 可视化结果")
    
    # 检查是否有示例图像
    example_images = []
    for ext in ['*.jpg', '*.jpeg', '*.png', '*.bmp']:
        import glob
        example_images.extend(glob.glob(ext))
    
    if len(example_images) >= 2:
        print(f"\n发现示例图像: {example_images[:2]}")
        print("可以使用这些图像进行测试")
        
        # 自动测试
        try:
            result = analyzer.compare_images(example_images[0], example_images[1])
            print(f"\n自动测试结果:")
            for hash_type, data in result['results'].items():
                print(f"{hash_type}: 相似度 {data['similarity']:.2f}%")
        except Exception as e:
            print(f"自动测试失败: {e}")
    
    print("\n使用方法:")
    print("1. 创建分析器: analyzer = ImageSimilarityAnalyzer()")
    print("2. 比较图像: result = analyzer.compare_images('image1.jpg', 'image2.jpg')")
    print("3. 可视化结果: analyzer.visualize_comparison(result)")
    print("4. 查找相似图像: similar = analyzer.find_similar_images('target.jpg', ['img1.jpg', 'img2.jpg'])")
    
    print("\n支持的哈希算法:")
    print("- aHash (平均哈希): 快速，对缩放敏感")
    print("- pHash (感知哈希): 准确，对缩放不敏感")
    print("- dHash (差异哈希): 快速，对缩放敏感")
    print("- wHash (小波哈希): 准确，需要pywt库")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
图像相似度算法性能评估脚本
包含精确率、召回率、F1分数等量化指标
"""

import cv2
import numpy as np
import os
import matplotlib.pyplot as plt
from image_hash import ImageHash
import time

class PerformanceEvaluator:
    """算法性能评估器"""
    
    def __init__(self):
        # 设置中文字体
        plt.rcParams["font.family"] = ["Microsoft YaHei", "SimHei", "Arial"]
    
    def create_test_dataset(self, base_image_path, output_dir="test_dataset"):
        """创建测试数据集"""
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        
        # 读取基础图像
        base_img = cv2.imread(base_image_path)
        if base_img is None:
            raise Exception(f"无法读取基础图像: {base_image_path}")
        
        # 创建相似图像（轻微变换）
        similar_images = []
        
        # 1. 轻微压缩
        for quality in [95, 90, 85]:
            compressed_path = os.path.join(output_dir, f"similar_compressed_{quality}.jpg")
            cv2.imwrite(compressed_path, base_img, [int(cv2.IMWRITE_JPEG_QUALITY), quality])
            similar_images.append(compressed_path)
        
        # 2. 轻微缩放
        for scale in [0.95, 1.05]:
            h, w = base_img.shape[:2]
            new_size = (int(w * scale), int(h * scale))
            scaled_img = cv2.resize(base_img, new_size)
            # 缩放回原尺寸
            scaled_back = cv2.resize(scaled_img, (w, h))
            scaled_path = os.path.join(output_dir, f"similar_scaled_{scale}.jpg")
            cv2.imwrite(scaled_path, scaled_back)
            similar_images.append(scaled_path)
        
        # 3. 轻微亮度调整
        for brightness in [-10, 10]:
            hsv = cv2.cvtColor(base_img, cv2.COLOR_BGR2HSV)
            h, s, v = cv2.split(hsv)
            v = cv2.add(v, brightness)
            v = np.clip(v, 0, 255)
            adjusted_hsv = cv2.merge((h, s, v))
            adjusted_img = cv2.cvtColor(adjusted_hsv, cv2.COLOR_HSV2BGR)
            brightness_path = os.path.join(output_dir, f"similar_brightness_{brightness}.jpg")
            cv2.imwrite(brightness_path, adjusted_img)
            similar_images.append(brightness_path)
        
        # 创建不相似图像（随机噪声）
        dissimilar_images = []
        for i in range(5):
            # 添加随机噪声
            noise = np.random.randint(0, 50, base_img.shape, dtype=np.uint8)
            noisy_img = cv2.add(base_img, noise)
            dissimilar_path = os.path.join(output_dir, f"dissimilar_noise_{i}.jpg")
            cv2.imwrite(dissimilar_path, noisy_img)
            dissimilar_images.append(dissimilar_path)
        
        # 创建测试用例
        test_cases = []
        
        # 相似图像对
        for similar_img in similar_images:
            test_cases.append((base_image_path, similar_img, True))
        
        # 不相似图像对
        for dissimilar_img in dissimilar_images:
            test_cases.append((base_image_path, dissimilar_img, False))
        
        return test_cases, similar_images, dissimilar_images
    
    def evaluate_single_algorithm(self, test_cases, algorithm_name, algorithm_func):
        """评估单个算法的性能"""
        print(f"\n评估 {algorithm_name} 算法:")
        print("-" * 50)
        
        thresholds = [0.5, 0.6, 0.7, 0.8, 0.9]
        results = {}
        
        for threshold in thresholds:
            metrics = ImageHash.evaluate_algorithm_performance(
                test_cases, algorithm_func, threshold
            )
            results[threshold] = metrics
            
            print(f"阈值 {threshold}:")
            print(f"  精确率 (Precision): {metrics['precision']:.4f}")
            print(f"  召回率 (Recall): {metrics['recall']:.4f}")
            print(f"  F1分数: {metrics['f1_score']:.4f}")
            print(f"  准确率 (Accuracy): {metrics['accuracy']:.4f}")
            print(f"  混淆矩阵: TP={metrics['tp']}, FP={metrics['fp']}, TN={metrics['tn']}, FN={metrics['fn']}")
            print()
        
        return results
    
    def compare_all_algorithms(self, test_cases):
        """比较所有算法的性能"""
        algorithms = {
            'pHash': ImageHash.phash,
            'dHash': ImageHash.dhash,
            'SSIM': ImageHash.ssim,
            '直方图': ImageHash.histogram_similarity
        }
        
        all_results = {}
        
        for alg_name, alg_func in algorithms.items():
            print(f"\n{'='*60}")
            print(f"评估 {alg_name} 算法")
            print('='*60)
            all_results[alg_name] = self.evaluate_single_algorithm(test_cases, alg_name, alg_func)
        
        return all_results
    
    def plot_performance_comparison(self, all_results, output_dir="performance_results"):
        """绘制性能比较图表"""
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        
        thresholds = [0.5, 0.6, 0.7, 0.8, 0.9]
        metrics = ['precision', 'recall', 'f1_score', 'accuracy']
        
        for metric in metrics:
            plt.figure(figsize=(12, 8))
            
            for alg_name, results in all_results.items():
                values = [results[threshold][metric] for threshold in thresholds]
                plt.plot(thresholds, values, marker='o', label=alg_name, linewidth=2)
            
            plt.title(f'{metric.upper()} 性能比较', fontsize=16, fontweight='bold')
            plt.xlabel('相似度阈值', fontsize=12)
            plt.ylabel(f'{metric.upper()}', fontsize=12)
            plt.legend(fontsize=10)
            plt.grid(True, alpha=0.3)
            plt.ylim(0, 1.05)
            
            # 保存图表
            plot_path = os.path.join(output_dir, f'{metric}_comparison.png')
            plt.tight_layout()
            plt.savefig(plot_path, dpi=300, bbox_inches='tight')
            plt.close()
            
            print(f"已保存 {metric.upper()} 比较图表: {plot_path}")
    
    def plot_roc_curves(self, test_cases, output_dir="performance_results"):
        """绘制ROC曲线"""
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        
        algorithms = {
            'pHash': ImageHash.phash,
            'dHash': ImageHash.dhash,
            'SSIM': ImageHash.ssim,
            '直方图': ImageHash.histogram_similarity
        }
        
        plt.figure(figsize=(10, 8))
        
        # 绘制对角线 (随机分类器)
        plt.plot([0, 1], [0, 1], 'k--', alpha=0.5, label='随机分类器 (AUC=0.5)')
        
        auc_scores = {}
        
        for alg_name, alg_func in algorithms.items():
            print(f"生成 {alg_name} 的ROC数据...")
            roc_data = ImageHash.generate_roc_data(test_cases, alg_func)
            
            if roc_data is not None:
                plt.plot(roc_data['fpr'], roc_data['tpr'], 
                        label=f'{alg_name} (AUC={roc_data["auc"]:.3f})', 
                        linewidth=2)
                auc_scores[alg_name] = roc_data['auc']
        
        plt.title('ROC曲线比较', fontsize=16, fontweight='bold')
        plt.xlabel('假正例率 (FPR)', fontsize=12)
        plt.ylabel('真正例率 (TPR)', fontsize=12)
        plt.legend(fontsize=10)
        plt.grid(True, alpha=0.3)
        plt.xlim(0, 1)
        plt.ylim(0, 1)
        
        # 保存ROC曲线图
        roc_path = os.path.join(output_dir, 'roc_curves.png')
        plt.tight_layout()
        plt.savefig(roc_path, dpi=300, bbox_inches='tight')
        plt.close()
        
        print(f"已保存ROC曲线图: {roc_path}")
        
        # 打印AUC排名
        print("\nAUC排名:")
        print("-" * 30)
        sorted_auc = sorted(auc_scores.items(), key=lambda x: x[1], reverse=True)
        for i, (alg_name, auc) in enumerate(sorted_auc, 1):
            print(f"{i}. {alg_name}: {auc:.4f}")
        
        return auc_scores
    
    def generate_performance_report(self, all_results, auc_scores=None, output_dir="performance_results"):
        """生成性能评估报告"""
        if not os.path.exists(output_dir):
            os.makedirs(output_dir)
        
        report_path = os.path.join(output_dir, "performance_report.txt")
        
        with open(report_path, "w", encoding="utf-8") as f:
            f.write("图像相似度算法性能评估报告\n")
            f.write("=" * 50 + "\n\n")
            f.write(f"评估时间: {time.strftime('%Y-%m-%d %H:%M:%S')}\n\n")
            
            # 添加AUC信息
            if auc_scores:
                f.write("【AUC (ROC曲线下面积) 排名】\n")
                f.write("-" * 30 + "\n")
                sorted_auc = sorted(auc_scores.items(), key=lambda x: x[1], reverse=True)
                for i, (alg_name, auc) in enumerate(sorted_auc, 1):
                    f.write(f"{i}. {alg_name}: {auc:.4f}\n")
                f.write("\n")
            
            thresholds = [0.5, 0.6, 0.7, 0.8, 0.9]
            
            for alg_name, results in all_results.items():
                f.write(f"【{alg_name} 算法】\n")
                f.write("-" * 30 + "\n")
                
                # 写入表头
                f.write(f"{'阈值':<8} {'精确率':<10} {'召回率':<10} {'F1分数':<10} {'准确率':<10}\n")
                f.write("-" * 50 + "\n")
                
                # 写入数据
                for threshold in thresholds:
                    metrics = results[threshold]
                    f.write(f"{threshold:<8} {metrics['precision']:<10.4f} {metrics['recall']:<10.4f} "
                           f"{metrics['f1_score']:<10.4f} {metrics['accuracy']:<10.4f}\n")
                
                f.write("\n")
            
            # 最佳性能总结
            f.write("【最佳性能总结】\n")
            f.write("-" * 30 + "\n")
            
            for threshold in thresholds:
                f.write(f"\n阈值 {threshold} 下的最佳算法:\n")
                best_algs = {}
                
                for alg_name, results in all_results.items():
                    metrics = results[threshold]
                    best_algs[alg_name] = {
                        'precision': metrics['precision'],
                        'recall': metrics['recall'],
                        'f1_score': metrics['f1_score'],
                        'accuracy': metrics['accuracy']
                    }
                
                # 找出各项指标的最佳算法
                best_precision = max(best_algs.items(), key=lambda x: x[1]['precision'])
                best_recall = max(best_algs.items(), key=lambda x: x[1]['recall'])
                best_f1 = max(best_algs.items(), key=lambda x: x[1]['f1_score'])
                best_accuracy = max(best_algs.items(), key=lambda x: x[1]['accuracy'])
                
                f.write(f"  最高精确率: {best_precision[0]} ({best_precision[1]['precision']:.4f})\n")
                f.write(f"  最高召回率: {best_recall[0]} ({best_recall[1]['recall']:.4f})\n")
                f.write(f"  最高F1分数: {best_f1[0]} ({best_f1[1]['f1_score']:.4f})\n")
                f.write(f"  最高准确率: {best_accuracy[0]} ({best_accuracy[1]['accuracy']:.4f})\n")
        
        print(f"性能评估报告已生成: {report_path}")

def main():
    """主函数"""
    print("图像相似度算法性能评估")
    print("=" * 50)
    
    # 检查是否有测试图像
    test_image = "test_image.jpg"  # 请替换为实际的测试图像路径
    
    if not os.path.exists(test_image):
        print(f"错误: 找不到测试图像 {test_image}")
        print("请将测试图像命名为 'test_image.jpg' 并放在当前目录")
        return
    
    # 创建评估器
    evaluator = PerformanceEvaluator()
    
    # 创建测试数据集
    print("创建测试数据集...")
    test_cases, similar_images, dissimilar_images = evaluator.create_test_dataset(test_image)
    
    print(f"测试数据集创建完成:")
    print(f"  相似图像对: {len(similar_images)} 对")
    print(f"  不相似图像对: {len(dissimilar_images)} 对")
    print(f"  总测试用例: {len(test_cases)} 个")
    
    # 评估所有算法
    all_results = evaluator.compare_all_algorithms(test_cases)
    
    # 生成图表和报告
    print("\n生成性能比较图表...")
    evaluator.plot_performance_comparison(all_results)
    
    print("\n生成ROC曲线...")
    auc_scores = evaluator.plot_roc_curves(test_cases)
    
    print("\n生成性能评估报告...")
    evaluator.generate_performance_report(all_results, auc_scores)
    
    print("\n性能评估完成！")

if __name__ == "__main__":
    main()

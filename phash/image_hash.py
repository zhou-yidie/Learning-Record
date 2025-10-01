import cv2
import numpy as np
import os
from PIL import Image, ImageTk
import tkinter as tk
from tkinter import filedialog, ttk, messagebox
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import time
import math

class ImageHash:
    """图像哈希算法类，实现pHash和dHash算法"""
    
    @staticmethod
    def phash(image_path, hash_size=8, highfreq_factor=4):
        """
        感知哈希算法(pHash)实现
        :param image_path: 图像路径
        :param hash_size: 哈希大小
        :param highfreq_factor: 高频因子
        :return: 64位哈希字符串
        """
        try:
            # 读取图像
            img = cv2.imread(image_path)
            if img is None:
                raise Exception(f"无法读取图像: {image_path}")
                
            # 调整图像大小
            size = hash_size * highfreq_factor
            img = cv2.resize(img, (size, size), interpolation=cv2.INTER_AREA)
            
            # 转换为灰度图
            img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            
            # 计算DCT变换
            dct = cv2.dct(np.float32(img))
            
            # 取DCT的左上角部分(低频成分)
            dct_low_freq = dct[:hash_size, :hash_size]
            
            # 计算平均值(排除第一个元素)
            avg = np.mean(dct_low_freq[1:])
            
            # 生成哈希
            hash_str = ""
            for i in range(hash_size):
                for j in range(hash_size):
                    hash_str += "1" if dct_low_freq[i, j] > avg else "0"
            
            return hash_str
        except Exception as e:
            print(f"pHash计算错误: {str(e)}")
            return None
    
    @staticmethod
    def dhash(image_path, hash_size=8):
        """
        差异哈希算法(dHash)实现
        :param image_path: 图像路径
        :param hash_size: 哈希大小
        :return: 64位哈希字符串
        """
        try:
            # 读取图像
            img = cv2.imread(image_path)
            if img is None:
                raise Exception(f"无法读取图像: {image_path}")
                
            # 调整图像大小为(hash_size+1, hash_size)
            img = cv2.resize(img, (hash_size + 1, hash_size), interpolation=cv2.INTER_AREA)
            
            # 转换为灰度图
            img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            
            # 生成哈希
            hash_str = ""
            for i in range(hash_size):
                for j in range(hash_size):
                    # 比较相邻像素
                    hash_str += "1" if img[i, j] < img[i, j + 1] else "0"
            
            return hash_str
        except Exception as e:
            print(f"dHash计算错误: {str(e)}")
            return None
    
    @staticmethod
    def hamming_distance(hash1, hash2):
        """
        计算两个哈希值的汉明距离
        :param hash1: 第一个哈希字符串
        :param hash2: 第二个哈希字符串
        :return: 汉明距离
        """
        if len(hash1) != len(hash2):
            raise ValueError("两个哈希值长度必须相同")
        
        # 位运算实现 - 更高效
        int1 = int(hash1, 2)
        int2 = int(hash2, 2)
        return bin(int1 ^ int2).count('1')
    
    @staticmethod
    def ssim(image_path1, image_path2, window_size=11, k1=0.01, k2=0.03):
        """
        计算结构相似性指数(SSIM) - 完整实现
        :param image_path1: 第一张图像路径
        :param image_path2: 第二张图像路径
        :param window_size: 滑动窗口大小
        :param k1, k2: SSIM算法常数
        :return: SSIM值
        """
        try:
            # 读取图像并转换为灰度图
            img1 = cv2.imread(image_path1)
            img2 = cv2.imread(image_path2)
            
            if img1 is None or img2 is None:
                raise Exception("无法读取图像")
                
            # 确保图像大小一致
            img2 = cv2.resize(img2, (img1.shape[1], img1.shape[0]))
            
            # 转换为灰度图
            img1_gray = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
            img2_gray = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
            
            # 转换为float类型
            img1_float = img1_gray.astype(np.float64)
            img2_float = img2_gray.astype(np.float64)
            
            # SSIM常数
            c1 = (k1 * 255) ** 2
            c2 = (k2 * 255) ** 2
            
            # 计算均值
            mu1 = cv2.GaussianBlur(img1_float, (window_size, window_size), 1.5)
            mu2 = cv2.GaussianBlur(img2_float, (window_size, window_size), 1.5)
            
            mu1_sq = mu1 * mu1
            mu2_sq = mu2 * mu2
            mu1_mu2 = mu1 * mu2
            
            # 计算方差和协方差
            sigma1_sq = cv2.GaussianBlur(img1_float * img1_float, (window_size, window_size), 1.5) - mu1_sq
            sigma2_sq = cv2.GaussianBlur(img2_float * img2_float, (window_size, window_size), 1.5) - mu2_sq
            sigma12 = cv2.GaussianBlur(img1_float * img2_float, (window_size, window_size), 1.5) - mu1_mu2
            
            # 计算SSIM
            ssim_map = ((2 * mu1_mu2 + c1) * (2 * sigma12 + c2)) / ((mu1_sq + mu2_sq + c1) * (sigma1_sq + sigma2_sq + c2))
            
            # 返回平均SSIM值
            return np.mean(ssim_map)
            
        except Exception as e:
            print(f"SSIM计算错误: {str(e)}")
            return None
    
    @staticmethod
    def histogram_similarity(image_path1, image_path2):
        """
        计算直方图相似度
        :param image_path1: 第一张图像路径
        :param image_path2: 第二张图像路径
        :return: 直方图相似度
        """
        try:
            # 读取图像
            img1 = cv2.imread(image_path1)
            img2 = cv2.imread(image_path2)
            
            if img1 is None or img2 is None:
                raise Exception("无法读取图像")
                
            # 确保图像大小一致
            img2 = cv2.resize(img2, (img1.shape[1], img1.shape[0]))
            
            # 计算直方图
            hist1 = cv2.calcHist([img1], [0, 1, 2], None, [8, 8, 8], [0, 256, 0, 256, 0, 256])
            hist2 = cv2.calcHist([img2], [0, 1, 2], None, [8, 8, 8], [0, 256, 0, 256, 0, 256])
            
            # 归一化直方图
            hist1 = cv2.normalize(hist1, hist1).flatten()
            hist2 = cv2.normalize(hist2, hist2).flatten()
            
            # 计算巴氏距离并转换为相似度
            distance = cv2.compareHist(hist1, hist2, cv2.HISTCMP_BHATTACHARYYA)
            return 1 - distance  # 转换为相似度，值越大越相似
        except Exception as e:
            print(f"直方图相似度计算错误: {str(e)}")
            return None
    
    @staticmethod
    def evaluate_algorithm_performance(test_cases, algorithm_func, threshold=0.8):
        """
        评估算法性能指标
        :param test_cases: 测试用例列表，格式: [(image1_path, image2_path, is_similar), ...]
        :param algorithm_func: 算法函数 (如 phash, dhash, ssim, histogram_similarity)
        :param threshold: 相似度阈值
        :return: 性能指标字典
        """
        tp = fp = tn = fn = 0
        
        for image1_path, image2_path, is_similar in test_cases:
            try:
                # 计算相似度
                similarity = algorithm_func(image1_path, image2_path)
                
                if similarity is None:
                    continue
                
                # 根据阈值判断预测结果
                predicted_similar = similarity >= threshold
                
                # 更新混淆矩阵
                if is_similar and predicted_similar:
                    tp += 1  # 真正例
                elif not is_similar and predicted_similar:
                    fp += 1  # 假正例
                elif not is_similar and not predicted_similar:
                    tn += 1  # 真负例
                elif is_similar and not predicted_similar:
                    fn += 1  # 假负例
                    
            except Exception as e:
                print(f"评估错误: {str(e)}")
                continue
        
        # 计算性能指标
        precision = tp / (tp + fp) if (tp + fp) > 0 else 0
        recall = tp / (tp + fn) if (tp + fn) > 0 else 0
        f1_score = 2 * (precision * recall) / (precision + recall) if (precision + recall) > 0 else 0
        accuracy = (tp + tn) / (tp + tn + fp + fn) if (tp + tn + fp + fn) > 0 else 0
        
        return {
            'precision': precision,
            'recall': recall,
            'f1_score': f1_score,
            'accuracy': accuracy,
            'tp': tp,
            'fp': fp,
            'tn': tn,
            'fn': fn,
            'total': tp + fp + tn + fn
        }
    
    @staticmethod
    def generate_roc_data(test_cases, algorithm_func, thresholds=None):
        """
        生成ROC曲线数据
        :param test_cases: 测试用例列表
        :param algorithm_func: 算法函数
        :param thresholds: 阈值列表，默认为0.0到1.0的100个点
        :return: ROC数据字典
        """
        if thresholds is None:
            thresholds = [i/100.0 for i in range(0, 101)]
        
        # 计算所有测试用例的相似度
        similarities = []
        true_labels = []
        
        for image1_path, image2_path, is_similar in test_cases:
            try:
                similarity = algorithm_func(image1_path, image2_path)
                if similarity is not None:
                    similarities.append(similarity)
                    true_labels.append(1 if is_similar else 0)
            except Exception as e:
                print(f"ROC数据生成错误: {str(e)}")
                continue
        
        if not similarities:
            return None
        
        # 计算每个阈值下的TPR和FPR
        tpr_list = []
        fpr_list = []
        
        for threshold in thresholds:
            tp = fp = tn = fn = 0
            
            for similarity, true_label in zip(similarities, true_labels):
                predicted = 1 if similarity >= threshold else 0
                
                if true_label == 1 and predicted == 1:
                    tp += 1
                elif true_label == 0 and predicted == 1:
                    fp += 1
                elif true_label == 0 and predicted == 0:
                    tn += 1
                elif true_label == 1 and predicted == 0:
                    fn += 1
            
            # 计算TPR和FPR
            tpr = tp / (tp + fn) if (tp + fn) > 0 else 0
            fpr = fp / (fp + tn) if (fp + tn) > 0 else 0
            
            tpr_list.append(tpr)
            fpr_list.append(fpr)
        
        # 计算AUC (使用梯形法则)
        auc = ImageHash._calculate_auc(fpr_list, tpr_list)
        
        return {
            'fpr': fpr_list,
            'tpr': tpr_list,
            'thresholds': thresholds,
            'auc': auc,
            'similarities': similarities,
            'true_labels': true_labels
        }
    
    @staticmethod
    def _calculate_auc(fpr_list, tpr_list):
        """计算AUC值"""
        auc = 0
        for i in range(1, len(fpr_list)):
            auc += (fpr_list[i] - fpr_list[i-1]) * (tpr_list[i] + tpr_list[i-1]) / 2
        return auc
    
    @staticmethod
    def compare_algorithms_performance(test_cases, thresholds=None):
        """
        比较多种算法的性能
        :param test_cases: 测试用例列表
        :param thresholds: 阈值列表，默认为 [0.5, 0.6, 0.7, 0.8, 0.9]
        :return: 性能比较结果
        """
        if thresholds is None:
            thresholds = [0.5, 0.6, 0.7, 0.8, 0.9]
        
        algorithms = {
            'pHash': ImageHash.phash,
            'dHash': ImageHash.dhash,
            'SSIM': ImageHash.ssim,
            '直方图': ImageHash.histogram_similarity
        }
        
        results = {}
        
        for alg_name, alg_func in algorithms.items():
            results[alg_name] = {}
            for threshold in thresholds:
                metrics = ImageHash.evaluate_algorithm_performance(
                    test_cases, alg_func, threshold
                )
                results[alg_name][threshold] = metrics
        
        return results
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
using namespace cv;
string pHashValue(Mat &srcImg);//pHash方法计算图片哈希值
int hanmingDist(string &str1, string &str2);//计算哈希值字符串的汉明距离

int main()
{
	Mat orgImg = imread("image1.jpg");
	Mat img = imread("image2.jpg");

	if (orgImg.empty() || img.empty())
	{
		cerr << "图片加载失败，请检查路径" << endl;
		return 1;
	}

	imshow("OrgImg", orgImg);
	imshow("Img", img);

	string str1 = pHashValue(orgImg);
	string str2 = pHashValue(img);

	int distance = hanmingDist(str1, str2);
	cout << "两张图片的汉明距离：" << distance << endl;

	if (distance < 5) //若汉明距离小于5，则两张图片相似
    {
		cout << "两张图片相似" << endl;
	}
	else
	{
		cout << "两张图片不相似" << endl;
	}

	waitKey(0);
	return 0;
}

string pHashValue(Mat &srcImg)//pHash方法计算图片哈希值
{
	Mat img, dstImg;
	string rst(64, '\0');

	double dIndex[64];
	double mean = 0.0;
	int  k = 0;

	if (srcImg.channels() == 3)//若为彩色图像则转换为灰度图像
	{
		cvtColor(srcImg, srcImg, CV_BGR2GRAY);
		img = Mat_<double>(srcImg);
	}
	else
	{

		img = Mat_<double>(srcImg);

	}

	//缩放尺寸
	resize(img, img, Size(32, 32));
	//离散余弦变换 DCT
	dct(img, dstImg);

	//获取dct系数均值
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			dIndex[k] = dstImg.at<double>(i, j);
			//计算每个像素的均值
			mean += dstImg.at<double>(i, j) / 64;
			++k;
		}
	}

	//计算hash
	for (int i = 0; i < 64; ++i)
	{
		if (dIndex[i] >= mean)
		{
			rst[i] = '1';
		}
		else {
			rst[i] = '0';
		}
	}

	return rst;

}
int hanmingDist(string &str1, string &str2)//计算哈希值字符串的汉明距离
{
	if ((str1.size() != 64) || (str2.size() != 64))
	{
		return -1;
	}

	int distValue = 0;
	for (int i = 0; i < 64; i++)
	{
		if (str1[i] != str2[i])
		{
			distValue++;
		}
	}

	return distValue;

}


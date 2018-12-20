#pragma once
#include <iostream>
#include <algorithm>
#include <climits>
#include <fstream>
#include <iomanip>
#include <vector>
#include "math.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>//换版本后需要多加的头文件
//彭腿友情提供
#include "MyDetector.h"
#include "QRImageInfo.h"
#include "pixelVisibility.h"
using namespace std;
using namespace cv;
struct weight {      
	double distance; //权重
	int piontAcontourindex, piontAindex, piontBcontourindex, piontBindex; // A B 的索引
};
struct index {
	int piontcontourindex, piontindex; // A B 的索引
};
class Connection
{
private:
	vector<vector<int>> label;//每个像素的lable;
	vector <vector<Vec2i>> boundary_pixel;
	vector<vector<Point>> contours;//独立区域 即 分支 的轮廓点集
	vector<vector<weight>> weights;//维护各分支轮廓的各点权重的集合 
public:
	Connection();
	~Connection();

	//获得分支，获得各个分支的轮廓 存到contours数组中 返回独立分支的个数
	int get_lable(const char* inputImage);
	//获得各分支轮廓 
	void get_all_boundary(const char* inputImage);

	//得到一个点的可见点集合 用索引值表示 
	vector<Point> get_visibility(int piontAcontourindex, int piontAindex);
	//计算两点间的带权距离 权重 返回A点最小的权重 ，对应的B点的所属分支索引 以及分支中的点索引 定义为结构体weight
	weight degree_distance(int piontAcontourindex, int piontAindex);
	//计算该分支的最小权重 返回该分支的最小权重 A B 的索引
	weight contour_distace(int contourindex);
	//一次连接处理
	void merge(weight min);
	//对输入图像进行连通处理

};


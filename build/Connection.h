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
#include <opencv2/imgproc/types_c.h>//���汾����Ҫ��ӵ�ͷ�ļ�
//���������ṩ
#include "MyDetector.h"
#include "QRImageInfo.h"
#include "pixelVisibility.h"
using namespace std;
using namespace cv;
struct weight {      
	double distance; //Ȩ��
	int piontAcontourindex, piontAindex, piontBcontourindex, piontBindex; // A B ������
};
struct index {
	int piontcontourindex, piontindex; // A B ������
};
class Connection
{
private:
	vector<vector<int>> label;//ÿ�����ص�lable;
	vector <vector<Vec2i>> boundary_pixel;
	vector<vector<Point>> contours;//�������� �� ��֧ �������㼯
	vector<vector<weight>> weights;//ά������֧�����ĸ���Ȩ�صļ��� 
public:
	Connection();
	~Connection();

	//��÷�֧����ø�����֧������ �浽contours������ ���ض�����֧�ĸ���
	int get_lable(const char* inputImage);
	//��ø���֧���� 
	void get_all_boundary(const char* inputImage);

	//�õ�һ����Ŀɼ��㼯�� ������ֵ��ʾ 
	vector<Point> get_visibility(int piontAcontourindex, int piontAindex);
	//���������Ĵ�Ȩ���� Ȩ�� ����A����С��Ȩ�� ����Ӧ��B���������֧���� �Լ���֧�еĵ����� ����Ϊ�ṹ��weight
	weight degree_distance(int piontAcontourindex, int piontAindex);
	//����÷�֧����СȨ�� ���ظ÷�֧����СȨ�� A B ������
	weight contour_distace(int contourindex);
	//һ�����Ӵ���
	void merge(weight min);
	//������ͼ�������ͨ����

};


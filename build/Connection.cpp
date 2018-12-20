#include "Connection.h"
using namespace std;
using namespace cv;

Connection::Connection()
{
}
Connection::~Connection()
{
}
int Connection::get_lable(const char* inputImage) 
{
	//得到分支
	cv::Mat srcImg = imread(inputImage, cv::IMREAD_COLOR);
	//cv::bitwise_xor(srcImg, cv::Scalar(255, 255, 255), srcImg);
	cv::Mat gray;
	cv::cvtColor(srcImg, gray, CV_BGR2GRAY);
	//2値化
	int threshval = 100;
	cv::Mat bin = threshval < 128 ? (gray < threshval) : (gray > threshval);
	//反相处理：
	cv::bitwise_xor(bin, cv::Scalar(255, 255, 255), bin);
	//求联通区域
	cv::Mat labelImage(bin.size(), CV_32S);
	//int nLabels = cv::connectedComponents(bin, labelImage, 8);
	int nLabels = connectedComponents(bin, labelImage, 4);
	std::vector<cv::Vec3b> colors(nLabels);
	colors[0] = cv::Vec3b(0, 0, 0);

	//output_info << "Number of connected components = " << nLabels - 1 << std::endl << std::endl;
	//output_info << "Number of connected components = " << nLabels << std::endl << std::endl;

	for (int label = 1; label < nLabels; label++)
	{
		colors[label] = cv::Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
		//output_info << "Component " << label << std::endl;

	}

	cv::Mat dst(srcImg.size(), CV_8UC3);

	for (int r = 0; r < dst.rows; r++)
	{
		std::vector<int> cur_vector;
		for (int c = 0; c < dst.cols; c++)
		{
			int cur_lable = labelImage.at<int>(r, c);
			cv::Vec3b &pixel = dst.at<cv::Vec3b>(r, c);
			pixel = colors[cur_lable];

			cur_vector.push_back(cur_lable);
		}
		label.push_back(cur_vector);
	}

	//std::ofstream file("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/label_image.txt");
	//for (int i = 0; i < label.size(); i++)
	//{
	//	for (int j = 0; j < label[i].size(); j++)
	//	{
	//		file << " " << label[i][j];
	//	}
	//	file << "" << std::endl;
	//	//cout << label[i].size() << endl;
	//}
	//cout << label.size()<<endl;
	//imwrite("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/colores_label.png", dst);


	return nLabels;
}
void Connection::get_all_boundary(const char* inputImage) {

	//for (int i = 1; i < n; i++) {
	//	int current_lable = i;
	//	//传入实参（给定lable编号）时，获取boundary的像素值
	//	//  label.size()是列数，相当于y
	//	std::vector < cv::Vec2i> vectors;
	//	std::vector < cv::Point> points;
	//	for (int i = 1; i < label.size() - 1; i++)
	//	{
	//		//label[[i].size()是行数，相当于y
	//		for (int j = 1; j < label[i].size() - 1; j++)
	//		{
	//			if (label[i][j] == current_lable)
	//			{
	//				if ((label[i - 1][j] == 0 || label[i][j - 1] == 0) || (label[i + 1][j] == 0 || label[i][j + 1] == 0 ))
	//				{
	//					cv::Vec2i v(i, j);
	//					vectors.push_back(v);

	//					cv:Point p(i, j);
	//					points.push_back(p);
	//				}
	//			}
	//		}
	//	};
	//	boundary_pixel.push_back(vectors);
	//	contours.push_back(points);
	//}

	Mat src = cv::imread(inputImage);
	Mat gray2(src.size(), CV_8U);
	cvtColor(src, gray2, CV_BGR2GRAY);//转换成灰度图  
	threshold(gray2, gray2, 128, 255, cv::THRESH_BINARY);//转换成2值图像  

	vector<vector<Point>> temcontours;
	findContours(gray2,
		contours, // a vector of contours   
		RETR_LIST, // retrieve the external contours  
		CV_CHAIN_APPROX_NONE); // retrieve all pixels of each contours  

							   // Print contours' length 

	
	for (int i = 0; i < contours.size(); i++)
	{
		std::reverse(contours[i].begin(), contours[i].end());
	}

	cout << "Contours: " << contours.size() << std::endl;



	//out for debug
	ofstream file2("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/boundary_info.txt");
	for (int i = 0; i < contours.size(); i++) 
	{
		file2 << "boundary " << i << " :" << std::endl;
		for (int j = 0; j < contours[i].size(); j++) {
			file2 << contours[i][j].y << " " << contours[i][j].x << std::endl;
		}
	}
	//visual for debug
	Mat canvas = cv::imread("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/test-v.png");
	std::vector<cv::Vec3b> colors(contours.size());
	for (int label = 0; label < contours.size(); label++)
	{
		colors[label] = cv::Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
	}
	for (int r = 0; r < contours.size(); r++)
	{
		for (int c = 0; c < contours[r].size(); c++)
		{
			cv::Vec3b &pixel = canvas.at<cv::Vec3b>(contours[r][c].y, contours[r][c].x);
			pixel = colors[r];
		}
	}
	imwrite("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/color_contours.png", canvas);
}
vector<Point> Connection::get_visibility(int piontAcontourindex, int piontAindex) {
	vector<Point> contourin;
	for (int i = 0; i <= contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
		{
			contourin.push_back(contours[i][j]);
		}
	}

	vector<Point> piont_visualContour;
	piont_visualContour = conn::pixelVisibility(contours[piontAcontourindex][piontAindex], contourin);

	//visual for debug
	Mat canvas = cv::imread("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/test-v.png");
	Vec3b red(0,0,255);
	Vec3b black(0, 0, 0);
	for (int r = 0; r < contours.size(); r++)
	{
		for (int c = 0; c < contours[r].size(); c++)
		{
			cv::Vec3b &pixel = canvas.at<cv::Vec3b>(contours[r][c].x, contours[r][c].y);
			pixel = black;
		}
	}
	for (int i = 0; i < piont_visualContour.size() ; i++)
	{
		cv::Vec3b &pixel = canvas.at<cv::Vec3b>(piont_visualContour[i].x, piont_visualContour[i].y);
		pixel = red;
	}
	imwrite("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/point_visualContour.png", canvas);

	return piont_visualContour;
}
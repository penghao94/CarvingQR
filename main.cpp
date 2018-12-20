#include <string>
#include <fstream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include "StabilityDectection.h"
#include "AxisDetection.h"
#include "Connection.h"
int main()
{
	using namespace std;
	using namespace cv;

	//connection
	Connection code;
	int lablenum = code.get_lable("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/test.png");
	code.get_all_boundary("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/test.png");
	code.get_visibility(2, 5);
	//detect::StabilityDectection code;
	//vector<vector<Point>> contours = code.dectect_lable("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/code3_ccc4.png");
	//int random = 1;
	//vector<double> onepiontFC = code.piont_field_connection("file/contours.png", 1, 90);
	//vector<double> onecontourFC = code.contour_field_connection("file/contours.png", 0);
	//code.img_field_connection("file/contours.png");
	//code.visualimg_field_connectiona("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/contours.png");

	/*------------------ - 中轴的方法没啥用 dis------------------------ - */
	//detect::AxisDetection code;
	//code.disboufield("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/code3_c.png");
	//code.visual_field_Laplacian("D:/workplace/visual studio 2015/QRcode/CarvingQR/data/code.png", "D:/workplace/visual studio 2015/QRcode/CarvingQR/data/diff_ledfield.png");
	/*------------------ - 中轴的方法没啥用 dis end------------------------ - */
	system("pause");
}

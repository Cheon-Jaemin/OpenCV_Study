#include <opencv2/opencv.hpp>
using namespace cv;

int main(void) 
{
	Mat img_gray;
	img_gray= imread("sign.png", IMREAD_GRAYSCALE);
	
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	
	Mat img_result1;
	dilate(img_gray, img_result1, kernel, Point(-1, -1), 1); //∆ÿ√¢
	Mat img_result2;
	dilate(img_gray, img_result2, kernel, Point(-1, -1), 2);
	Mat img_result3;
	dilate(img_gray, img_result3, kernel, Point(-1, -1), 3);
	
	imshow("Input", img_gray);
	imshow("Result1", img_result1);
	imshow("Result2", img_result2);
	imshow("Result3", img_result3);
	
	waitKey(0);
	return 0;}
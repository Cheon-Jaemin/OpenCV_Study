#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(void)
{
	Mat img_color = imread("colors.png", IMREAD_COLOR);

	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

	Mat img_binary;
	threshold(img_gray, img_binary, 200, 255, THRESH_BINARY_INV);
	imshow("binary", img_gray);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);
	imshow("morphologEX", img_binary);

	vector<vector<Point>> contours;
	findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_NONE);

	drawContours(img_color, contours, -1, Scalar(0, 0, 0), 2);

	imshow("result", img_color);
	
	waitKey(0);
	return 0;
}
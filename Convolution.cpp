#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat img;
	img = imread("cat.png");

	Mat kernel = Mat(7, 7, CV_32F, Scalar(1 / 25.0));
	Mat dst;

	filter2D(img, dst, -1, kernel);
	imshow("original", img);
	imshow("result", dst);
	waitKey(0);
}
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(void)
{
	Mat img1, img2;

	img1 = imread("stadi.png", IMREAD_COLOR);
	img2 = imread("log.png", IMREAD_COLOR);

	Mat dst;
	addWeighted(img1, 0.7, img2, 0.3, 0, dst);

	imshow("dst", dst);
	waitKey(0);
}

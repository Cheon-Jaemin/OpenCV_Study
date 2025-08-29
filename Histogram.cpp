#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;int main(int ac, char** av){	Mat img_1 = imread("lena.png", 0);	Mat hist_img;	equalizeHist(img_1, hist_img);	imshow("Original", img_1);	imshow("Histogram", hist_img);	waitKey(0);	return 0;}
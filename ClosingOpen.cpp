#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{
	Mat img_gray = imread("test3.png", IMREAD_GRAYSCALE);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat img_result;
	morphologyEx(img_gray, img_result, MORPH_CLOSE, kernel);
	
	imshow("input", img_gray);
	imshow("result", img_result);

	waitKey(0);
	return 0;
}
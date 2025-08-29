#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{
	Mat img_gray = imread("test2_Dilate.png", IMREAD_GRAYSCALE);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat img_result;
	morphologyEx(img_gray, img_result, MORPH_OPEN, kernel);

	imshow("input", img_gray);
	imshow("result", img_result);

	waitKey(0);
	return 0;
}

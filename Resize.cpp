#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{
	Mat img_color;
	img_color = imread("flower.jpg");
	imshow("original", img_color);

	int width = img_color.cols;
	int height = img_color.rows;

	Mat img_result;
	resize(img_color, img_result, Size(), 2, 2, INTER_CUBIC);
	imshow("x2 INTER_CUBIC", img_result);

	resize(img_color, img_result, Size(3 * width, 3 * height), INTER_LINEAR);
	imshow("x3 INTER_LINEAR", img_result);

	resize(img_color, img_result, Size(), 0.5, 0.5, INTER_AREA);
	imshow("x0.5 INTER_AREA", img_result);

	waitKey(0);
	return 0;
}

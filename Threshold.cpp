#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{
	Mat img_color;
	img_color = imread("Moon.png", IMREAD_GRAYSCALE);
	imshow("img_color", img_color);

	threshold(img_color, img_color, 3, 255, THRESH_BINARY);
	imshow("img_color1", img_color);

	waitKey(0);
}

#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{
	Mat img;
	img = imread("orange.png");
	Mat img_blur;
	GaussianBlur(img, img_blur, Size(5, 5), 0);
	imshow("Original", img);
	imshow("Result", img_blur);

	waitKey(0);
}

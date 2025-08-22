#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{
	Mat image_color = imread("apple.png", IMREAD_COLOR);
	int width = image_color.cols;
	int height = image_color.rows;

	Mat image_gray(height, width, CV_8UC1);

	for (int y = 0; y < height; y++)
	{
		uchar* input = image_color.ptr<uchar>(y);
		uchar* output = image_gray.ptr<uchar>(y);
		for (int x = 0; x < width; x++)
		{
			uchar b = input[x * 3 + 0];
			uchar g = input[x * 3 + 1];
			uchar r = input[x * 3 + 2];

			output[x] = r * 0.2126 + g * 0.7152 + b * 0.0722;
		}
	}
	imshow("color", image_color);
	imshow("result", image_gray);
	waitKey(0);
}
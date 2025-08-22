#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Point2f src[3];
int idx = 0;
Mat img_color;

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		src[idx] = Point2f(x, y);
		idx++;
		cout << "(" << x << ", " << y << ")" << endl;
		circle(img_color, Point(x, y), 3, Scalar(0, 0, 255), -1);
	}
}

int main(void)
{
	namedWindow("source");
	setMouseCallback("source", mouse_callback);
	img_color = imread("flower.jpg");

	while (1)
	{
		imshow("source", img_color);
		if (waitKey(1) == 32)
		{
			break;
		}
	}
	int height = img_color.rows;
	int width = img_color.cols;

	Point2f dst[3];   
	dst[0] = src[0];
	dst[1] = Point2f(src[1].x, src[1].y + 100);
	dst[2] = src[2];

	Mat M = getAffineTransform(src, dst);

	Mat img_result;
	warpAffine(img_color, img_result, M, Size(width, height));
	imshow("result", img_result);

	waitKey(0);
	return 0;
}

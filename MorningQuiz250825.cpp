#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Point2f s[3];
int idx = 0;
Mat img;

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		s[idx] = Point2f(x, y);
		idx++;
		circle(img, Point(x, y), 3, Scalar(255, 0, 0), -1);
	}
}

int main(void)
{
	namedWindow("background");
	setMouseCallback("background", mouse_callback);
	img = imread("background.png");

	while (true)
	{
		imshow("background", img);
		if (waitKey(1) == 32)
		{
			break;
		}
	}

	Point2f dst[3];
	dst[0] = s[0];
	dst[1] = Point2f(s[1].x, s[1].y + 150);
	dst[2] = s[2];

	Mat M = getAffineTransform(s, dst);

	Mat result;
	warpAffine(img, result, M, Size(img.rows, img.cols));
	imshow("result", result);

	waitKey(0);
	return 0;
}
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int sx = 0;
int sy = 0;
int ex = 0;
int ey= 0;

float sc = 1.f;

int step = 3;
int lx = 0;
int ly = 0;

void mouse_callback(int ev, int x, int y, int flags, void* p)
{
	if (ev == EVENT_LBUTTONDOWN)
	{
		sx = x;
		sy = y;
		step = 1;
	}
	if (ev == EVENT_MOUSEMOVE) {}
	if (ev == EVENT_LBUTTONUP)
	{
		ex = x;
		ey = y;
		step = 2;
	}
	if (ev == EVENT_MOUSEWHEEL)
	{
		if (flags > 0)
		{
			sc *= 2.f;
		}
		else
		{
			sc++;
		}
		if (flags < 0)
		{
			sc /= 2.f;
		}
		step = 3;
	}
}

int main(void)
{
	namedWindow("LINE");
	setMouseCallback("LINE", mouse_callback);
	Mat img = imread("line.jpg");

	float fangle = 0.f;

	Mat res = img.clone();
	Point2f Pos(res.cols / 2, res.rows / 2);

	while (1)
	{
		if (step == 3)
		{
			Mat M = getRotationMatrix2D(Point2f(res.cols / 2, res.rows / 2), fangle, sc);
			warpAffine(img, res, M, Size(res.cols, res.rows));

			Mat M2(2, 3, CV_64F, Scalar(0, 0));
			M2.at<double>(0, 0) = 1;
			M2.at<double>(1, 1) = 1;
			M2.at<double>(0, 2) = Pos.x - res.cols / 2;
			M2.at<double>(1, 2) = Pos.y - res.rows / 2;

			warpAffine(res, res, M2, Size(res.cols, res.rows));
		}
		if (step == 2)
		{
			lx = ex - sx;
			ly = ey - sy;
			
			Mat M2(2, 3, CV_64F, Scalar(0, 0));
			M2.at<double>(0, 0) = 1;
			M2.at<double>(1, 1) = 1;
			M2.at<double>(0, 2) = lx;
			M2.at<double>(1, 2) = ly;

			warpAffine(res, res, M2, Size(res.cols, res.rows));
			Pos = { Pos.x + lx, Pos.y + ly };
			step = 0;
		}
		imshow("LINE", res);
		
		if (waitKey(0) == 97)
		{
			fangle += 10.f;
			step = 3;
		}
		else if (waitKey(0) == 115)
		{
			fangle -= 10.f;
			step = 3;
		}
		else if (waitKey(0) == 27)
		{
			return 0;
		}
	}
	return 0;
}
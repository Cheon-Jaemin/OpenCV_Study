#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
	int width = 640;
	int height = 680;

	Mat img(width, height, CV_8UC3, Scalar(0, 0, 0));
	Point center(int(width / 2), int(height / 2));
	int rot = 0;

	while (1)
	{
		ellipse(img, center, Size(200, 10), rot, 0, 360, Scalar(255, 255, 255), 3);
		ellipse(img, center, Size(30, 200), rot, 0, 360, Scalar(0, 0, 255), 3);
		ellipse(img, center, Size(200, 200), 0, 0, 360, Scalar(0, 0, 255), 3);
		ellipse(img, center, Size(200, 100), rot, 0, 360, Scalar(100, 0, 0), 3);
		ellipse(img, center, Size(130, 200), rot, 0, 360, Scalar(100, 255, 25), 3);
		ellipse(img, center, Size(20, 200), 0, 0, 360, Scalar(255, 255, 255), 3);
		rot += 1;
		imshow("res", img);

		if (rot > 720)
		{
			rot = 0;
			img = Scalar(0, 0, 0);
		}
		if (waitKey(1) == 27)
		{
			break;
		}
	}
}
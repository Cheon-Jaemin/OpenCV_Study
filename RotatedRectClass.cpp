#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void main(void)
{
	RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f);
	Point2f pts[4];
	rr1.points(pts);

	Rect rr2 = rr1.boundingRect();
	cout << "rr1 center" << rr1.center << endl;
	cout << "rr1 size" << rr1.size << endl;
	cout << "rr1 angle" << rr1.angle << endl;
	cout << "rr2" << rr2 << endl;
	
	for (int i = 0; i < 4; i++)
	{
		cout << "pts[" << i << "]" << pts[i] << endl;
	}

	Mat image(400, 400, CV_8UC3, Scalar(255, 255, 255));
	for (int i = 0; i < 4; i++)
	{
		line(image, pts[i], pts[(i + 1) % 4], Scalar(0, 0, 255));
		rectangle(image, rr2, Scalar(255, 0, 0));
		imshow("image", image);
	}
	waitKey();
}

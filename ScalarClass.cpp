#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void main(void)
{
	Scalar gray(128);
	Scalar blue(255, 0, 0);
	Scalar green(0 ,255, 0);
	Scalar red(0, 0, 255);
	Scalar transparent(0, 0, 255, 128);

	cout << "Gray : " << gray << endl;
	cout << "Blue : " << blue << endl;
	cout << "Green : " << green << endl;
	cout << "Red : " << red << endl;
	cout << "Transparent Red : " << transparent << endl;

	Mat img1(100, 100, CV_8UC3, blue);
	imshow("Blue Image", img1);
	waitKey(0);

	return;
}

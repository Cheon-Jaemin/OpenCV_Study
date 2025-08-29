#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(void)
{
	VideoCapture cap(0, CAP_DSHOW);
	while (true)
	{
		Mat img;
		bool ret = cap.read(img);

		int width = img.cols;
		int height = img.rows;
		int center_x = img.cols / 2.0;
		int center_y = img.rows / 2.0;

		Mat roi(img, Rect(center_x - 100, center_y - 100, 100, 100));
		Scalar m = mean(roi);

		Mat img_mean(roi.rows, roi.cols, CV_8UC3, Scalar(m[0], m[1], m[2]));

		imshow("mean", img_mean);
		imshow("roi", img);

		if (waitKey(1) == 27)
		{
			break;
		}
	}
	cap.release();
	return 0;
}
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(void)
{
	Mat img_frame;
	VideoCapture cap(0, CAP_DSHOW);
	if (!cap.isOpened())
	{
		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}

	while (true)
	{
		bool ret = cap.read(img_frame);
		if (!ret)
		{
			cout << "캡쳐 실패" << endl;
			break;
		}

		Mat img_hsv;
		cvtColor(img_frame, img_hsv, COLOR_BGR2HSV);

		Mat img_mask;

		Vec3b lower_blue = Vec3b(120 - 20, 30, 0);
		Vec3b upper_blue = Vec3b(120 + 20, 255, 255);
		inRange(img_hsv, lower_blue, upper_blue, img_mask);

		Mat img_result;
		bitwise_and(img_frame, img_frame, img_result, img_mask);

		imshow("Color", img_frame);
		imshow("Result", img_result);

		if (waitKey(1) == 27)
		{
			break;
		}
	}
	cap.release();
	return 0;
}
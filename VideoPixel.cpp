#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
	Mat img_color;
	Mat img_gray;

	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}

	while (1)
	{
		bool ret = cap.read(img_color);
		if (!ret)
		{
			cout << "캡쳐 실패" << endl;
			break;
		}
		cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
		int height = img_color.rows;
		int width = img_color.cols;

		for (int y = 0; y < height; y++)
		{
			uchar* pointer_input = img_color.ptr<uchar>(y);
			uchar* pointer_output = img_gray.ptr<uchar>(y);
			for (int x = 0; x < width; x++)
			{
				uchar b = pointer_input[x * 3 + 0];
				uchar g = pointer_input[x * 3 + 1];
				uchar r = pointer_input[x * 3 + 2];
				pointer_output[x] = r * 0.2126 + g * 0.7152 + b * 0.0722;
			}
		}

		Mat img_result;
		cvtColor(img_gray, img_result, COLOR_GRAY2BGR);
		for (int y = 80; y < 250; y++)
		{
			uchar* pointer_input = img_result.ptr<uchar>(y);
			for (int x = 250; x < 310; x++)
			{
				pointer_input[x * 3 + 0] = 0;
				pointer_input[x * 3 + 1] = 255;
				pointer_input[x * 3 + 2] = 0;
			}
		}

		imshow("color", img_color);
		imshow("result", img_result);
		int key = waitKey(1);
		if (key == 27)
		{
			break;
		}
	}
	cap.release();
	waitKey(0);
}

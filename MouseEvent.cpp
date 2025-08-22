#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void* param)
{
	switch (event)
	{
		case EVENT_LBUTTONDOWN:
		{
			cout << "���콺 ���ʹ�ư ������" << endl;
			break;
		}
		case EVENT_RBUTTONDOWN:
		{
			cout << "���콺 �����ʹ�ư ������" << endl;
			break;
		}
		case EVENT_RBUTTONUP:
		{
			cout << "���콺 �����ʹ�ư ����" << endl;
			break;
		}
		case EVENT_LBUTTONDBLCLK:
		{
			cout << "���콺 ���ʹ�ư ����Ŭ��" << endl;
			break;
		}
	}
}

int main(void)
{
	Mat image(200, 300, CV_8U);
	image.setTo(255);
	imshow("���콺 �̺�Ʈ1", image);
	imshow("���콺 �̺�Ʈ2", image);

	setMouseCallback("���콺 �̺�Ʈ1", onMouse, 0);
	waitKey(0);
}
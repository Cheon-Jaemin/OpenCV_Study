#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(void)
{
	Mat img_frame;
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "ī�޶� �� �� �����ϴ�." << endl;
		return -1;
	}

	int step = 1;
	//������ ����� �����ϱ� ���� ����� ����
	
	while (1)
	{
		//img_frame������ ����� �̹����� �����쿡 �����ְ� ��
		//ó������ ī�޶󿡼� ĸ�ĵ� �÷� �̹����� ������ ��
		bool ret = cap.read(img_frame);
		if (!ret)
		{
			cout << "ĸ�� ����" << endl;
			break;
		}

		int key = waitKey(1);

		if (key == 27)
		{
			break;
		}
		//1��Ű �ԷµǸ� ������ ���
		else if (key == 49)
		{
			step = 1;
		}
		//2��Ű �ԷµǸ� �׷��̽����� ���� ���
		else if (key == 50)
		{
			step = 2;
		}
		//3��Ű �ԷµǸ� �������� ���� ���
		else if (key == 51)
		{
			step = 3;
		}

		//step�� 2�̻��̸� �׷��̽����� �̹��� ����
		if (step > 1)
		{
			cvtColor(img_frame, img_frame, COLOR_BGR2GRAY);
		}
		
		//step�� 3�̻��̸� ���� �̹����� �����
		if (step > 2)
		{
			Canny(img_frame, img_frame, 60, 90);
		}
		//�տ��� ó���� ����� ���� �ٸ� �̹����� Result�����쿡 �������� ��
		imshow("Result", img_frame);
	}
	cap.release();
}
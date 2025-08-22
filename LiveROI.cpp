#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int start_x, start_y, end_x, end_y, step = 0;
// ���콺 �̺�Ʈ�� ����/�� ��ǥ �� ���� �ܰ踦 �����ϴ� ����

Mat frame;
void swap(int& x, int& y) 
{					//�Լ��� �Ű����� x�� y�� ����(reference) Ÿ��
	int temp = x;	//x�� y�� �Լ� ȣ�� �� ���޵Ǵ� ���� ������ �� �ٸ� �̸��� ��
	x = y;			// x�� �����ϴ�(��, ���� ���� ������) ���� ���� �ӽ� ���� temp�� ����
	y = temp;		// x�� ���� ���� �����鼭 x�� ���ο� ���� �Ҵ��ϱ� ���� �ʼ��� 
}

// ���콺 �̺�Ʈ �ݹ� �Լ�
// �� �Լ��� "Color" â���� ���콺 �̺�Ʈ�� �߻��� ������ ȣ��
// e: �߻��� ���콺 �̺�Ʈ Ÿ�� (��: EVENT_LBUTTONDOWN, EVENT_MOUSEMOVE, EVENT_LBUTTONUP)
// x, y: ���콺 Ŀ���� ���� x, y ��ǥ
// f: ���콺 �̺�Ʈ �߻� �� ������ �÷��� (��: EVENT_FLAG_LBUTTON)
// void*: ����� ������ (���⼭�� ������� ����)
void cb_ms(int e, int x, int y, int f, void*)
{
	if (e == EVENT_LBUTTONDOWN) 
	{				 // ���콺 ���� ��ư�� ������ ��
		step = 1;
		start_x = x; // ���� x ��ǥ ����
		start_y = y; // ���� y ��ǥ ����
	}
	else if (e == EVENT_MOUSEMOVE && f == EVENT_FLAG_LBUTTON) 
	{
		step = 2; // �ܰ踦 2�� ���� (�簢�� �׸��� ��)
		end_x = x; // ���� x ��ǥ�� �� x ��ǥ�� ����
		end_y = y; // ���� y ��ǥ�� �� y ��ǥ�� ����
	}
	else if (e == EVENT_LBUTTONUP)
	{
		step = 3;
		end_x = x; // ���� x ��ǥ ����
		end_y = y; // ���� y ��ǥ ����
	}
}

int main()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "ī�޶� �� �� �����ϴ�." << endl;
		return -1;
	}
	namedWindow("Color");
	// ���콺 �̺�Ʈ�� �߻��ϸ� cb_ms �Լ��� ȣ��
	setMouseCallback("Color", cb_ms);
	while (true)
	{
		bool ret = cap.read(frame);
		if (!ret)
		{
			cout << "ĸó ����!" << endl;
			return -1;
		}
		// �������� ���̿� �ʺ�
		int h = frame.rows;
		int w = frame.cols;
		// step ���� ���� �ٸ� �۾��� ����
		switch (step)
		{
			// ���콺 ���� ��ư�� ���� ���� (������ ǥ��)
			// �������� ��� ���� �׸�
			// frame: �׸��� �׸� �̹���
			// Point(start_x, start_y): ���� �߽� ��ǥ
			// 10: ���� ������
			// Scalar(0, 255, 0): ���� ���� (BGR ����: �Ķ�, �ʷ�, ����) -> ���⼭�� ���
			// -1: ���� ä�� ������ (����) �ƴϸ� �׵θ��� �׸� ������ (���) -> -1�� ä���
		case 1:
		{
			circle(frame, Point(start_x, start_y), 10, Scalar(0, 255, 0), -1); // �� �׸���
			break;
		}
		case 2:
		{
			rectangle(frame, Point(start_x, start_y), Point(end_x, end_y), Scalar(0, 255, 0), 3); // �簢�� �׸���
			break;
		}
		case 3:
		{
			if (end_x < 0) // ���콺�� �������� �������
				end_x = 0;
			if (end_y < 0) // ���콺�� ���� �������
				end_y = 0;
			if (end_x > w) // ���콺�� ���������� �������
				end_x = w;
			if (end_y > h) // ���콺�� �Ʒ��� �������
				end_y = h;
			// start_x�� end_x, start_y�� end_y�� ������ �ùٸ��� ����
			// �簢���� � �������� �巡���ϴ��� �׻� (min_x, min_y)���� (max_x, max_y)�� �ǵ��� ��
			if (start_x > end_x)
			{ // ���콺�� �����ʿ��� ��������
				swap(start_x, end_x);
			}
			if (start_y > end_y)
			{// ���콺�� �Ʒ����� ����
				swap(start_y, end_y);
			}
			// �������� ������ ������ (Ŭ���� �� ���) ROI�� 1x1 �ȼ��� �ǵ��� ����
			// 0x0 ROI�� ������ ������ �� �ֱ� ������ 1�� ������ ������
			if (start_x == end_x && start_y == end_y)
			{
				end_x += 1;
				end_y += 1;
			}
			// frame �̹������� start_x, start_y�� ���������� �ϰ� end_x, end_y�� �������� �ϴ� �簢�� ������ ����
			Mat Roi(frame, Rect(Point(start_x, start_y), Point(end_x, end_y))); // ROI ����
			// ROI�� �÷�(BGR)���� ȸ������ ��ȯ
			// �÷� �̹����� BGR ä�η� �����Ǿ� �ְ�,
			// Canny ���� ������ ���� ä��(ȸ����) �̹����� �Է����� ����
			cvtColor(Roi, Roi, COLOR_BGR2GRAY);
			// Canny ���� ���� �˰����� ����
			// Roi: �Է� �̹��� (ȸ����)
			// Roi: ��� ���� �̹��� (�Է� �̹����� ������ Mat ��ü�� ����)
			// 150: ���� �Ӱ谪 (���� ����)
			// 50: ���� �Ӱ谪 (���� ����)
			// ���� ������ ���� �Ӱ谪���� ũ�� ������ �����ϰ�, ���� �Ӱ谪���� ������ ������ �ƴ�
			// ������ ���� �Ӱ谪 ���̿� �ִ� ������ ����Ǿ� ������ ������ ����
			Canny(Roi, Roi, 150, 50);
			// ���� ���� ����� ȸ���� �̹���(���� ä��)�̹Ƿ�, ���� �����ӿ� �ٽ� �����ϱ� ���� �÷�(BGR)�� ��ȯ
			// ���� �÷� �������� �ش� ��ġ�� ���� �̹����� ��� �� ����
			cvtColor(Roi, Roi, COLOR_GRAY2BGR);
			// ó���� ROI �̹����� ���� frame�� �ش� ��ġ�� ����
			// frame(Rect(...))�� frame Mat ��ü ���� ������ �簢�� ������ ���� ������ ��ȯ
			// Roi.copyTo()�� Roi Mat ��ü�� ������ �ش� ���� �������� ����
			Roi.copyTo(frame(Rect(Point(start_x, start_y), Point(end_x, end_y))));
			break;
		}
		}
		imshow("Color", frame);
		if (waitKey(25) > 0)
		{
			break;
		}
	}
	cap.release();
	destroyAllWindows();
}

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
	Mat img_color = imread("apple.jpg", IMREAD_COLOR);

	//�̹����� ���̿� �ʺ� ������
	//Mat��ü�� ����(�̹���)�� ����Ǿ� �ִٸ�
	int height = img_color.rows;	//Mat::rows������ ���� �ȼ�(��, y)
	int width = img_color.cols;		//Mat::cols������ ���� �ȼ�(��, x)

	//�׷��� ������ �̹����� ������ Mat��ü�� ����
	Mat img_gray(height, width, CV_8UC1); //8��Ʈ uchar, ä�� 1��, �׷��� ������

	//for���� ���鼭 (x,y)�� �ִ� �ȼ��� �ϳ��� ����
	for (int y = 0; y < height; y++)
	{
		//�ӵ� ����� ���� y��ǥ�� ����Ͽ� ������ ��ġ�� �̸� ���
		uchar* pointer_Input = img_color.ptr<uchar>(y);
		uchar* pointer_output = img_gray.ptr<uchar>(y);

		for (int x = 0; x < width; x++)
		{
			//�÷� �̹����� (x,y)�� �ִ� �ȼ��� bgrä���� ����
			//�� �ȼ��� bgr 3���� ä���� �ֱ� ������ x��ǥ�� 3�� ����
			//�ѹ��� 3���� �� �� �̵�
			//�׷��� ������ �̹����� ������ ��쿡�� 3�� ���� �ʿ䰡 ����(1ä���̱� ����)
			uchar b = pointer_Input[x * 3 + 0];
			uchar g = pointer_Input[x * 3 + 1];
			uchar r = pointer_Input[x * 3 + 2];

			//(x,y)��ġ�� �ȼ��� �׷��� ������ ���� �����
			//��ȯ�� ��� ���� ������ �̹���
			//BT.709�� ��õ� ������ ����ϴ� ���
			//����� ���� ����� ���� �ΰ�, �Ķ����� ���� �� �ΰ�, �ð������� �� ��Ȯ�� ��� ����� ���� ��������� ���
			pointer_output[x] = r * 0.2126 + g * 0.7152 + b * 0.0722;
		}
	}

	//��� �̹����� �÷��� ǥ���ϱ� ���� �÷� �̹����� ��ȯ
	Mat img_result;
	cvtColor(img_gray, img_result, COLOR_GRAY2BGR);	//�����ε��Ͽ� ����cvtColor(color,gray,��), cvtColor(gray,color,��)
	
	//y������ 150~200, x������ 200~250�� ������ �ȼ��� �ʷϻ� �ȼ��� ����
	for (int y = 300; y < 350; y++)
	{
		//y���� �����ּҰ�, 150���� ���� �ּҰ�
		uchar* pointer_input = img_result.ptr<uchar>(y);
		for (int x = 420; x < 470; x++)
		{
			pointer_input[x * 3 + 0] = 0;
			pointer_input[x * 3 + 1] = 255;	//�ϳ��� �ȼ��� bgr�� ���� �ǰ� ���� G���� 255���� �־���
			pointer_input[x * 3 + 2] = 0;
		}
	}

	//���� �̹����� ��� �̹����� ������
	imshow("color", img_color);
	imshow("result", img_result);
	
	waitKey(0);
}

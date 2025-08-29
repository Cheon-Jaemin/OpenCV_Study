#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	VideoCapture cap(0, CAP_DSHOW);
	if (!cap.isOpened())
	{
		cout << "ī�޶� �� �� �����ϴ�." << endl;
		return -1;
	}
	
	Mat img_color;
	while (1)
	{
		bool ret = cap.read(img_color);
		if (!ret)
		{
			cout << "ĸ�� ����" << endl;
			break;
		}
		if (img_color.empty())
		{
			cout << "�̹��� ������ ���� �� �����ϴ�." << endl;
			return -1;
		}
		//�׷��� �����Ϸ� ��ȯ �� ����ȭ�Ͽ� ���̳ʸ� �̹����� ��ȯ
		Mat img_gray;
		cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
		
		Mat img_binary;
		threshold(img_gray, img_binary, 150, 255, THRESH_BINARY_INV);//�Ӱ谪�� �ٲ㺸�鼭 üũ��
		
		//����ȭ ����� �����ϱ� ���� �������� �ݱ� ������ ����
		Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));//Ŀ���� ũ�⸦ �ٲ㺽
		morphologyEx(img_binary, img_binary, MORPH_ELLIPSE, kernel); //���������� ����� Ÿ�������� ����
		
		vector<vector<Point>> contours;
		
		//����� ����
		findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_NONE);
		
		drawContours(img_color, contours, -1, Scalar(214, 228, 255), 2);
		
		imshow("result", img_color);
		
		if (waitKey(1) == 27)
		{
			break;
		}
	}
	return 0;
}
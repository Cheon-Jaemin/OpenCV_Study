#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat img_color;
	img_color = imread("cat on laptop.jpg", IMREAD_GRAYSCALE);
	
	//clone �Լ��� ����Ͽ� Mat��ü img_color�� ���纻�� ����, ��������
	Mat img_copyed1 = img_color.clone(); //�������1
	Mat img_copyed2;
	
	//copyTo�Լ��� ����Ͽ� Mat��ü img_color�� ���纻�� ����
	img_color.copyTo(img_copyed2); //�������2
	
	//�ϳ��� Mat��ü�� ����ȭ�� �����غ�
	threshold(img_color, img_color, 127, 255, THRESH_BINARY);
	imshow("img_color", img_color); //ù��° �̹����� ����ȭ �ǰ� �ٸ� �̹����� ��ȭ���� ����
	imshow("img_copyed1", img_copyed1); //clone()�� ����� ���� ���簡 �̷���� ���纻�� ������ �����ּҰ� �޸�
	imshow("img_copyed2", img_copyed2);

	waitKey(0);
}
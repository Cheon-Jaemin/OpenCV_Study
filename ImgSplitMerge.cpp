#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat img_color;
	img_color = imread("color.png", IMREAD_COLOR); 
	//BGR�� 3�� ä���� ���յ� Multi-channel
	//�÷� �̹����� ä�κ��� �и�
	//img_channels�迭�� blue, green, red������ ä���� �����
	
	Mat img_channels[3]; 
	//split(�и�)�ؼ� 3���� ä���� ���� �迭 ����
	//void split(const Mat&src, Mat dest[ ]), ù��° �Ű������� �и��� ����, �ι�° �Ű������� �и��� ä�ε��� ����� �迭
	
	split(img_color, img_channels); 
	//b->0��° ���, g->1��° ���, R->2��° ��ҷ� �и�
	//�迭�̸� img_channels�� ���� 0��° �ּҰ� ���޵�
	//ä�κ� �̹����� �����Ͽ� �÷� ������ ������
	//blue�� red�� ������ �ٲٱ� ���� push_back()���
	
	vector<Mat> channels;
	channels.push_back(img_channels[2]); // 2��° ���ؽ��ڿ� 1��° �ε����� �� �ڿ� 0��° �ε����� ������
	channels.push_back(img_channels[1]);
	channels.push_back(img_channels[0]);
	
	Mat img_result;
	//void merge(Vector<Mat> src, Mat dest), ù��° �Ű����� �Է� ������ ���Ͱ�, �ι�° �Ű����� ��¿���
	//ä�� ����, 1�� ä�� ���� N���� Nä�� ���� 1���� ����
	merge(channels, img_result);
	
	imshow("Color", img_result);
	imshow("B", img_channels[0]);
	imshow("G", img_channels[1]);
	imshow("R", img_channels[2]);
	waitKey(0);
	return 0;
}
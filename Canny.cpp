#include <opencv2/opencv.hpp>
using namespace cv;

static void on_trackbar(int, void*)
{
}
//Ʈ���ٸ� ������ �� ���� ����Ǵ� �ݹ��Լ�
//Ʈ���ٷ� ������ Opencv�� ���� �� ����
//���⼭�� �ƹ������� �ʴ� ���� �Լ��� ����, Ʈ���� ������ �ݵ�� �ʿ���

int main(void)
{
	namedWindow("Canny");
	
	createTrackbar("low threshold", "Canny", 0, 1000, on_trackbar);
	createTrackbar("high threshold", "Canny", 0, 1000, on_trackbar);
	//Ʈ���� ����
	//Ʈ���� �̸�, �������̸�, Ʈ������ �ּڰ�, �ִ�, �ݹ��Լ� �Է�

	setTrackbarPos("low threshold", "Canny", 50);
	setTrackbarPos("high threshold", "Canny", 150);
	//Ʈ������ �ʱⰪ�� ����
	//Ʈ���� �̸�, Ʈ���ٰ� �پ��ִ� ������ �̸�, �����ʱⰪ���� Ʈ���ٿ� ����

	Mat img_color;
	img_color = imread("orange.png", IMREAD_COLOR);
	imshow("orange", img_color);
	
	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
	//�̹����� �׷��� �����Ϸ� �ҷ���
	//Canny �Լ��� �Է��� �׷��� ������ �̹������� ��.


	while (1)
	{
		int low = getTrackbarPos("low threshold", "Canny");
		int high = getTrackbarPos("high threshold", "Canny");
		//���� Ʈ������ ��ġ�� ������

		Mat img_canny;
		Canny(img_gray, img_canny, low, high);
		imshow("Canny", img_canny);
		//Ʈ���ٷκ��� ������ ������ ĳ���Լ��� �Ķ���� ����
		//�Է��̹���, ����̹���, �ּҰ�, �ִ밪

		if (waitKey(1) == 27)
		{
			break;
		}
	}
	destroyAllWindows();
}
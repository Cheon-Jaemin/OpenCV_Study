#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

string title = "Ʈ���� �̺�Ʈ";
Mat image;

void onChange(int value, void* userdata) // Ʈ���� �ݹ� �Լ�
{
	int add_value = value - 130; // -126 ~ 129����
	cout << "�߰� ȭ�Ұ�" << add_value << endl;

	Mat tmp = image + add_value; // ���� ��Ŀ� -126 ~ 129 ���̰� ���ϱ�
	imshow(title, tmp);
}

int main(void)
{
	int value = 130;
	image = Mat(300, 400, CV_8UC1, Scalar(120)); // 1ä�� uchar��� ����, �׷��� ����

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("��Ⱚ", title, &value, 255, onChange);
	//Ʈ���� �̸�, Ʈ���� ����� â�̸�, Ʈ���� ����
	//��, Ʈ�����ִ밪, �ݹ��Լ��̸�

	imshow(title, image);
	waitKey(0);
	return 0;
}

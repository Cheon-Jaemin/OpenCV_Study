#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(void)
{
	Mat image(200, 300, CV_8UC1, Scalar(255)); // 1ä�� uchar���, 255�� �ʱ�ȭ
	namedWindow("Ű���� �̺�Ʈ", WINDOW_AUTOSIZE);
	imshow("Ű���� �̺�Ʈ", image);

	while (1)
	{
		int key = waitKey(0);
		if (key == 27)
		{
			break;
		}
		else
		{
			cout << (char)key << "Ű �Է�" << endl;
		}
	}
}
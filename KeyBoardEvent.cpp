#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(void)
{
	Mat image(200, 300, CV_8UC1, Scalar(255)); // 1채널 uchar행렬, 255로 초기화
	namedWindow("키보드 이벤트", WINDOW_AUTOSIZE);
	imshow("키보드 이벤트", image);

	while (1)
	{
		int key = waitKey(0);
		if (key == 27)
		{
			break;
		}
		else
		{
			cout << (char)key << "키 입력" << endl;
		}
	}
}
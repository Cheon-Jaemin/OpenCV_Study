#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

string title = "트랙바 이벤트";
Mat image;

void onChange(int value, void* userdata) // 트랙바 콜백 함수
{
	int add_value = value - 130; // -126 ~ 129범위
	cout << "추가 화소값" << add_value << endl;

	Mat tmp = image + add_value; // 원본 행렬에 -126 ~ 129 사이값 더하기
	imshow(title, tmp);
}

int main(void)
{
	int value = 130;
	image = Mat(300, 400, CV_8UC1, Scalar(120)); // 1채널 uchar행렬 선언, 그레이 영상

	namedWindow(title, WINDOW_AUTOSIZE);
	createTrackbar("밝기값", title, &value, 255, onChange);
	//트랙바 이름, 트랙바 등록할 창이름, 트랙바 변경
	//값, 트랙바최대값, 콜백함수이름

	imshow(title, image);
	waitKey(0);
	return 0;
}

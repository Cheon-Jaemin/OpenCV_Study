#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0, CAP_DSHOW);
	if (!cap.isOpened())
	{
		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}
	Mat img_color;
	Mat img_gray;
	while (1)
	{
		bool ret = cap.read(img_color);
		if (!ret)
		{
			cout << "캡쳐 실패" << endl;
			break;
		}
		if (img_color.empty())
		{
			cout << "이미지 파일을 읽을 수 없습니다." << endl;
			return -1;
		}
		cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
		//Noise filtering이라고도 칭하며, 중앙값 블러링
		//원본이미지, medianblur될 이미지, 커널 사이즈
		medianBlur(img_gray, img_gray, 3);
		cvtColor(img_gray, img_color, COLOR_GRAY2BGR);
		
		vector<Vec3f> circles; //float타입 3채널 벡터 선언
		//캐니 에지 검출기의 임계값을 100으로 높이고 축적배열에서 원 검출을 위한 임계값을 50으로 높임
		HoughCircles(img_gray, circles, HOUGH_GRADIENT, 1, 20, 100, 70, 0, 0);
		
		for (size_t i = 0; i < circles.size(); i++)
		{
			Vec3i c = circles[i];
			Point center(c[0], c[1]);
			int radius = c[2];
			circle(img_color, center, radius, Scalar(0, 255, 0), 2);
			circle(img_color, center, 2, Scalar(0, 0, 255), 3);
		}
		imshow("detected circles", img_color);
		
		if (waitKey(1) == 27)
		{
			break;
		}
	}
	return 0;
}
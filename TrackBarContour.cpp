#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

static void on_trackbar(int, void*)
{
}

int main(void)
{
	//컬러로 이미지를 가져오
	VideoCapture cap(0, CAP_DSHOW);
	if (!cap.isOpened())
	{
		cout << "카메라 닫힘" << endl;
		return -1;
	}
	
	Mat img_color;
	
	namedWindow("result", WINDOW_NORMAL);
	createTrackbar("threshold", "result", 0, 255, on_trackbar);
	setTrackbarPos("threshold", "result", 150);
	
	while (1)
	{
		cap.read(img_color);
		
		//그레이 스케일로 변환 후 이진화하여 바이너리 이미지로 변환
		Mat img_gray;
		cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
		
		Mat img_binary;
		int value = getTrackbarPos("threshold", "result");
		threshold(img_gray, img_binary, value, 255, THRESH_BINARY_INV);
		
		//이진화 결과를 개선하기 위해 모폴로지 닫기 연산을 해줌(팽창을 한 뒤 침식)
		Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(img_binary, img_binary, MORPH_CLOSE, kernel);
		
		//x, y좌표 데이터 세트를 한 요소로 컨투어 표현하는 점들의 집합(어레이)선언
		vector<vector<Point>> contours;
		//컨투어를 검출, 컨투어의 일부 구간이 직선인 경우 시작 좌표와 끝 좌표만 저장
		findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
		
		//한번에 모든 컨투어를 그릴 수 있음
		drawContours(img_color, contours, -1, Scalar(218, 224, 255), 2);
		imshow("result", img_color);
		
		if (waitKey(1) == 27)
		{
			break;
		}
	}
	cap.release();
	return 0;
}
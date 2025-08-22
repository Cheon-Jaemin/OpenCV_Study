#include <opencv2/opencv.hpp>
using namespace cv;

static void on_trackbar(int, void*)
{
}
//트랙바를 조정할 때 마다 실행되는 콜백함수
//트랙바로 조정할 Opencv를 넣을 수 있음
//여기서는 아무일하지 않는 더미 함수로 정의, 트랙바 생성시 반드시 필요함

int main(void)
{
	namedWindow("Canny");
	
	createTrackbar("low threshold", "Canny", 0, 1000, on_trackbar);
	createTrackbar("high threshold", "Canny", 0, 1000, on_trackbar);
	//트랙바 생성
	//트랙바 이름, 윈도우이름, 트랙바의 최솟값, 최댓값, 콜백함수 입력

	setTrackbarPos("low threshold", "Canny", 50);
	setTrackbarPos("high threshold", "Canny", 150);
	//트랙바의 초기값을 설정
	//트랙바 이름, 트랙바가 붙어있는 윈도우 이름, 설정초기값으로 트랙바에 접근

	Mat img_color;
	img_color = imread("orange.png", IMREAD_COLOR);
	imshow("orange", img_color);
	
	Mat img_gray;
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
	//이미지를 그레이 스케일로 불러옴
	//Canny 함수의 입력은 그레이 스케일 이미지여야 함.


	while (1)
	{
		int low = getTrackbarPos("low threshold", "Canny");
		int high = getTrackbarPos("high threshold", "Canny");
		//현재 트랙바의 위치를 가져옴

		Mat img_canny;
		Canny(img_gray, img_canny, low, high);
		imshow("Canny", img_canny);
		//트랙바로부터 가져온 값으로 캐니함수의 파라미터 조정
		//입력이미지, 출력이미지, 최소값, 최대값

		if (waitKey(1) == 27)
		{
			break;
		}
	}
	destroyAllWindows();
}
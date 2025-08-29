#include <opencv2/opencv.hpp>
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
		//그레이 스케일로 변환 후 이진화하여 바이너리 이미지로 변환
		Mat img_gray;
		cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
		
		Mat img_binary;
		threshold(img_gray, img_binary, 150, 255, THRESH_BINARY_INV);//임계값을 바꿔보면서 체크함
		
		//이진화 결과를 개선하기 위해 모폴로지 닫기 연산을 해줌
		Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));//커널의 크기를 바꿔봄
		morphologyEx(img_binary, img_binary, MORPH_ELLIPSE, kernel); //모폴로지의 출력을 타원형으로 잡음
		
		vector<vector<Point>> contours;
		
		//컨투어를 검출
		findContours(img_binary, contours, RETR_LIST, CHAIN_APPROX_NONE);
		
		drawContours(img_color, contours, -1, Scalar(214, 228, 255), 2);
		
		imshow("result", img_color);
		
		if (waitKey(1) == 27)
		{
			break;
		}
	}
	return 0;
}
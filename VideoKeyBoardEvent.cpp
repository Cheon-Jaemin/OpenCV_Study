#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(void)
{
	Mat img_frame;
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}

	int step = 1;
	//보여줄 결과를 지정하기 위해 사용한 변수
	
	while (1)
	{
		//img_frame변수에 저장된 이미지를 윈도우에 보여주게 됨
		//처음에는 카메라에서 캡쳐된 컬러 이미지가 나오게 됨
		bool ret = cap.read(img_frame);
		if (!ret)
		{
			cout << "캡쳐 실패" << endl;
			break;
		}

		int key = waitKey(1);

		if (key == 27)
		{
			break;
		}
		//1번키 입력되면 원영상 출력
		else if (key == 49)
		{
			step = 1;
		}
		//2번키 입력되면 그레이스케일 영상 출력
		else if (key == 50)
		{
			step = 2;
		}
		//3번키 입력되면 에지검출 영상 출력
		else if (key == 51)
		{
			step = 3;
		}

		//step이 2이상이면 그레이스케일 이미지 저장
		if (step > 1)
		{
			cvtColor(img_frame, img_frame, COLOR_BGR2GRAY);
		}
		
		//step이 3이상이면 에지 이미지가 저장됨
		if (step > 2)
		{
			Canny(img_frame, img_frame, 60, 90);
		}
		//앞에서 처리된 결과에 따라 다른 이미지가 Result윈도우에 보여지게 됨
		imshow("Result", img_frame);
	}
	cap.release();
}
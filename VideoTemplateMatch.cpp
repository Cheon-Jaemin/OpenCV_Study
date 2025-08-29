#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std; 

vector<Point> detectedObjects;

int main()
{
	Mat img_frame;
	VideoCapture cap(0, CAP_DSHOW);
	if (!cap.isOpened())
	{
		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}
	//매칭할 동전 이미지 불러오기(그레이 스케일로)
	Mat img_template = imread("one_coin.png", IMREAD_GRAYSCALE);
	//그레이 스케일이 적용된 동전 이미지를 이진화 시켜준다
	Mat img_binarytemp;
	threshold(img_template, img_binarytemp, 0, 255, THRESH_BINARY | THRESH_OTSU);
	int w = img_template.cols;
	int h = img_template.rows;
	//이진화한 동전 이미지를 보여줌
	imshow("binarytemp", img_binarytemp);

	while (1)
	{
		bool ret = cap.read(img_frame);
		if (!ret)
		{
			cout << "캡처 실패" << endl;
			break;
		}
		//카메라의 영상을 그레이 스케일로 변환시키고 이진화를 진행
		Mat img_gray;
		cvtColor(img_frame, img_gray, COLOR_BGR2GRAY);
		Mat img_binary;
		threshold(img_gray, img_binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
		//이진화한 카메라 영상과 이진화한 동전 이미지를 템플릿 매칭 시킨다
		Mat result;
		matchTemplate(img_binary, img_binarytemp, result, TM_CCOEFF_NORMED);
		for (int x = 0; x < result.cols; x++)
		{
			for (int y = 0; y < result.rows; y++)
			{
				//임계값 0.95나 0.93으로 설정(0.9로 설정 하면 구멍뚤린 동전도 매칭이 됨)
				if (result.at<float>(y, x) > 0.95)
				{
					detectedObjects.push_back(Point(x, y));
					rectangle(img_frame, Point(x, y), Point(x + w, y + h), Scalar(0, 0, 255), 1);
				}
			}
		}
		imshow("result", img_frame);
		imshow("binary", img_binary);

		int key = waitKey(1);
		if (key == 27)
		{
			break;
		}
	} 
	cap.release();
	return 0;
}
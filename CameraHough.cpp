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
	
	Mat img_color, img_edge, img_result;
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
		Canny(img_color, img_edge, 50, 150);
		cvtColor(img_edge, img_result, COLOR_GRAY2BGR);

		//Vec<int,4>, 정수형 데이터 4개를 가지는 linesP를 선언함
		vector<Vec4i> linesP;
		HoughLinesP(img_edge, linesP, 1, CV_PI / 180, 100, 50, 3);
		for (size_t i = 0; i < linesP.size(); i++)
		{
			Vec4i l = linesP[i];
			line(img_result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
		}
		imshow("Source", img_color);
		imshow("Probabilistic Line Transform", img_result);
		
		if (waitKey(1) == 27)
		{
			break;
		}
	}
	return 0;
}
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//마우스 왼쪽 버튼 상태 체크를 위해 사용
bool mouse_is_pressing = false;
//현재 그리기 모드 선택을 위해 사용 (원/사각형)
bool drawing_mode = true;

//최초로 마우스 왼쪽 버튼 누른 위치를 저장하기 위해 사용
int start_x = -1;
int start_y = -1;

Scalar color(255, 255, 255);

//그린 결과를 저장할 이미지
Mat img;

RNG rng(543210);

void mouse_callback(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_MOUSEMOVE)
	{
		if (mouse_is_pressing == true)
		{
			if (drawing_mode == true)
			{
				rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
			}
			else
			{
				circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
			}
		}
	}
	else if (event == EVENT_LBUTTONDOWN)
	{
		color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

		start_x = x;
		start_y = y;
	}
	else if (event == EVENT_LBUTTONUP)
	{
		mouse_is_pressing = false;
		
		if (drawing_mode == true)
		{
			rectangle(img, Point(start_x, start_y), Point(x, y), color, -1);
		}
		else
		{
			circle(img, Point(start_x, start_y), max(abs(start_x - x), abs(start_y - y)), color, -1);
		}
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		drawing_mode = !drawing_mode;
	}
}

int main(void)
{
	int width = 500;
	int height = 500;
	img = Mat(height, width, CV_8UC3, Scalar(0, 0, 0));
	namedWindow("image");

	setMouseCallback("image", mouse_callback, 0);

	while (1)
	{
		imshow("image", img);
		int key = waitKey(1);
		if (key == 27)
		{
			break;
		}
	}
	destroyAllWindows();
}

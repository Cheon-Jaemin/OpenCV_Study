#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool mouse_is_pressing = false;
int start_x, start_y, end_x, end_y;
int step = 0;
Mat img_color;

void swap(int* v1, int* v2)
{
	int temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}

void mouse_callback(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		step = 1;
		mouse_is_pressing = true;
		start_x = x;
		start_y = y;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		if (mouse_is_pressing)
		{
			end_x = x;
			end_y = y;
			step = 2;
		}
	}
	else if (event == EVENT_LBUTTONUP)
	{
		mouse_is_pressing = false;
		end_x = x;
		end_y = y;
		step = 3;
	}
}

int main(void)
{
	VideoCapture cap(0, CAP_DSHOW);
	if (!cap.isOpened())
	{
		cout << "에러 - 카메라를 열 수 없습니다." << endl;
		return -1;
	}
	namedWindow("Color");
	setMouseCallback("Color", mouse_callback);

	while (1)
	{
		cap.read(img_color);
		if (img_color.empty())
		{
			cout << "캡쳐 실패" << endl;
			break;
		}

		int h = img_color.rows;
		int w = img_color.cols;
		switch (step)
		{
		case 1:
		
			circle(img_color, Point(start_x, start_y), 10, Scalar(0, 255, 0), -1);
			break;
		
		case 2:
		
			rectangle(img_color, Point(start_x, start_y), Point(end_x, end_y), Scalar(0, 255, 0), 3);
			break;
		
		case 3:
		
			if (end_x < 0)
			{ // 마우스가 왼쪽으로 벗어났을때
				end_x = 0;
			}
			if (end_y < 0)
			{ // 마우스가 위로 벗어났을때
				end_y = 0;
			}
			if (end_x > w)
			{// 마우스가 오른쪽으로 벗어났을때
				end_x = w;
			}
			if (end_y > h)
			{// 마우스가 아래로 벗어났을때
				end_y = h;
			}
			// start_x와 end_x, start_y와 end_y의 순서를 올바르게 정렬
			// 사각형을 어떤 방향으로 드래그하더라도 항상 (min_x, min_y)에서 (max_x, max_y)가 되도록 함
			if (start_x > end_x)
			{// 마우스가 오른쪽에서 왼쪽으로
				swap(start_x, end_x);
			}
			if (start_y > end_y)
			{// 마우스가 아래에서 위로
				swap(start_y, end_y);
			}
			// 시작점과 끝점이 같으면 (클릭만 한 경우) ROI가 1x1 픽셀이 되도록 조정
			// 0x0 ROI는 에러를 유발할 수 있기 때문에 1을 무조건 더해줌
			if (start_x == end_x && start_y == end_y)
			{
				end_x += 1;
				end_y += 1;
			}

			Mat ROI(img_color, Rect(start_x, start_y, end_x - start_x, end_y - start_y));

			cvtColor(ROI, ROI, COLOR_BGR2GRAY);
			adaptiveThreshold(ROI, ROI, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 4);
			cvtColor(ROI, ROI, COLOR_GRAY2BGR);

			ROI.copyTo(img_color(Rect(start_x, start_y, end_x - start_x, end_y - start_y)));
			break;
		
		}
		imshow("Color", img_color);

		if (waitKey(25) > 0)
		{
			break;
		}
	}
	destroyAllWindows();
	return 0;
}

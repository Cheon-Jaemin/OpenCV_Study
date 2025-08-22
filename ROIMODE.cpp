#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool mouse_is_pressing = false;
int start_x, start_y, end_x, end_y;

int step = 0;
int step1 = 1;
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
		cout << "에러 - 카메라를 열 수 없습니다.\n";
		return -1;
	}
	namedWindow("Color");
	setMouseCallback("Color", mouse_callback);

	while (true)
	{
		cap.read(img_color);
		if (img_color.empty())
		{
			cout << "캡쳐 실패\n";
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
			if (end_x < 0) end_x = 0;
			if (end_y < 0) end_y = 0;
			if (end_x > w) end_x = w;
			if (end_y > h) end_y = h;
			if (start_x > end_x)
			{
				swap(&start_x, &end_x);
			}
			if (start_y > end_y)
			{
				swap(&start_y, &end_y);
			}
			else if (start_x == end_x || start_y == end_y)
			{
				end_x = start_x + 1;
				end_y = start_y + 1;
			}
			Mat ROI(img_color, Rect(start_x, start_y, end_x - start_x, end_y - start_y));
			//키보드 1번=>Canny
			if (step1 == 1)
			{
				cvtColor(ROI, ROI, COLOR_BGR2GRAY);
				Canny(ROI, ROI, 150, 50);
				cvtColor(ROI, ROI, COLOR_GRAY2BGR);
			}
			if (step1 == 2)
			{
				cvtColor(ROI, ROI, COLOR_BGR2GRAY);
				// ADAPTIVE_THRESH_MEAN_C: 이웃 픽셀의 평균을 임계값으로 사용
				// 5: 블록 크기 (임계값을 계산할 이웃 픽셀의 크기, 홀수여야 함
				// 4: C (평균에서 뺄 상수 값)
				adaptiveThreshold(ROI, ROI, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 4);
				cvtColor(ROI, ROI, COLOR_GRAY2BGR);
			}
			//키보드 3번=>평균색
			if (step1 == 3)
			{
				// ROI 영역의 모든 픽셀을 계산된 평균 색상으로 채움
				Scalar m = mean(ROI);
				ROI = m;
			}
			ROI.copyTo(img_color(Rect(start_x, start_y, end_x - start_x, end_y - start_y)));
			break;
		}
		imshow("Color", img_color);

		int key = waitKey(1);
		if (key == 'q' || key == 27) { // 'q' 키 또는 ESC 키(ASCII 27)가 눌리면 루프를 종료
			break;
		}
		else if (key == '1') {
			step1 = 1; // Canny edge detection
		}
		else if (key == '2') {
			step1 = 2; // Adaptive thresholding
		}
		else if (key == '3') {
			step1 = 3; // Average color
		}
	}
	cap.release(); //웹캠 캡처 객체를 해제하여 시스템 리소스(웹캠 장치)를 반환
	// 생성된 모든 OpenCV GUI 창을 닫습니다.
	destroyAllWindows();
	return 0;
}

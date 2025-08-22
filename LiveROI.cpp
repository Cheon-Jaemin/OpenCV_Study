#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int start_x, start_y, end_x, end_y, step = 0;
// 마우스 이벤트의 시작/끝 좌표 및 현재 단계를 저장하는 변수

Mat frame;
void swap(int& x, int& y) 
{					//함수의 매개변수 x와 y는 참조(reference) 타입
	int temp = x;	//x와 y는 함수 호출 시 전달되는 실제 변수의 또 다른 이름이 됨
	x = y;			// x가 참조하는(즉, 실제 원본 변수의) 현재 값을 임시 변수 temp에 저장
	y = temp;		// x의 값을 잃지 않으면서 x에 새로운 값을 할당하기 위해 필수적 
}

// 마우스 이벤트 콜백 함수
// 이 함수는 "Color" 창에서 마우스 이벤트가 발생할 때마다 호출
// e: 발생한 마우스 이벤트 타입 (예: EVENT_LBUTTONDOWN, EVENT_MOUSEMOVE, EVENT_LBUTTONUP)
// x, y: 마우스 커서의 현재 x, y 좌표
// f: 마우스 이벤트 발생 시 눌려진 플래그 (예: EVENT_FLAG_LBUTTON)
// void*: 사용자 데이터 (여기서는 사용하지 않음)
void cb_ms(int e, int x, int y, int f, void*)
{
	if (e == EVENT_LBUTTONDOWN) 
	{				 // 마우스 왼쪽 버튼을 눌렀을 때
		step = 1;
		start_x = x; // 시작 x 좌표 저장
		start_y = y; // 시작 y 좌표 저장
	}
	else if (e == EVENT_MOUSEMOVE && f == EVENT_FLAG_LBUTTON) 
	{
		step = 2; // 단계를 2로 설정 (사각형 그리기 중)
		end_x = x; // 현재 x 좌표를 끝 x 좌표로 저장
		end_y = y; // 현재 y 좌표를 끝 y 좌표로 저장
	}
	else if (e == EVENT_LBUTTONUP)
	{
		step = 3;
		end_x = x; // 최종 x 좌표 저장
		end_y = y; // 최종 y 좌표 저장
	}
}

int main()
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}
	namedWindow("Color");
	// 마우스 이벤트가 발생하면 cb_ms 함수가 호출
	setMouseCallback("Color", cb_ms);
	while (true)
	{
		bool ret = cap.read(frame);
		if (!ret)
		{
			cout << "캡처 실패!" << endl;
			return -1;
		}
		// 프레임의 높이와 너비
		int h = frame.rows;
		int w = frame.cols;
		// step 값에 따라 다른 작업을 수행
		switch (step)
		{
			// 마우스 왼쪽 버튼을 누른 상태 (시작점 표시)
			// 시작점에 녹색 원을 그림
			// frame: 그림을 그릴 이미지
			// Point(start_x, start_y): 원의 중심 좌표
			// 10: 원의 반지름
			// Scalar(0, 255, 0): 원의 색상 (BGR 순서: 파랑, 초록, 빨강) -> 여기서는 녹색
			// -1: 원을 채울 것인지 (음수) 아니면 테두리만 그릴 것인지 (양수) -> -1은 채우기
		case 1:
		{
			circle(frame, Point(start_x, start_y), 10, Scalar(0, 255, 0), -1); // 공 그리기
			break;
		}
		case 2:
		{
			rectangle(frame, Point(start_x, start_y), Point(end_x, end_y), Scalar(0, 255, 0), 3); // 사각형 그리기
			break;
		}
		case 3:
		{
			if (end_x < 0) // 마우스가 왼쪽으로 벗어났을때
				end_x = 0;
			if (end_y < 0) // 마우스가 위로 벗어났을때
				end_y = 0;
			if (end_x > w) // 마우스가 오른쪽으로 벗어났을때
				end_x = w;
			if (end_y > h) // 마우스가 아래로 벗어났을때
				end_y = h;
			// start_x와 end_x, start_y와 end_y의 순서를 올바르게 정렬
			// 사각형을 어떤 방향으로 드래그하더라도 항상 (min_x, min_y)에서 (max_x, max_y)가 되도록 함
			if (start_x > end_x)
			{ // 마우스가 오른쪽에서 왼쪽으로
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
			// frame 이미지에서 start_x, start_y를 시작점으로 하고 end_x, end_y를 끝점으로 하는 사각형 영역을 선택
			Mat Roi(frame, Rect(Point(start_x, start_y), Point(end_x, end_y))); // ROI 영역
			// ROI를 컬러(BGR)에서 회색조로 변환
			// 컬러 이미지는 BGR 채널로 구성되어 있고,
			// Canny 에지 검출은 단일 채널(회색조) 이미지를 입력으로 받음
			cvtColor(Roi, Roi, COLOR_BGR2GRAY);
			// Canny 에지 검출 알고리즘을 적용
			// Roi: 입력 이미지 (회색조)
			// Roi: 출력 에지 이미지 (입력 이미지와 동일한 Mat 객체에 저장)
			// 150: 상위 임계값 (강한 에지)
			// 50: 하위 임계값 (약한 에지)
			// 에지 강도가 상위 임계값보다 크면 에지로 간주하고, 하위 임계값보다 작으면 에지가 아님
			// 상위와 하위 임계값 사이에 있는 에지는 연결되어 있으면 에지로 간주
			Canny(Roi, Roi, 150, 50);
			// 에지 검출 결과는 회색조 이미지(단일 채널)이므로, 원본 프레임에 다시 복사하기 위해 컬러(BGR)로 변환
			// 원본 컬러 프레임의 해당 위치에 에지 이미지를 덮어쓸 수 있음
			cvtColor(Roi, Roi, COLOR_GRAY2BGR);
			// 처리된 ROI 이미지를 원본 frame의 해당 위치에 복사
			// frame(Rect(...))는 frame Mat 객체 내의 지정된 사각형 영역에 대한 참조를 반환
			// Roi.copyTo()는 Roi Mat 객체의 내용을 해당 참조 영역으로 복사
			Roi.copyTo(frame(Rect(Point(start_x, start_y), Point(end_x, end_y))));
			break;
		}
		}
		imshow("Color", frame);
		if (waitKey(25) > 0)
		{
			break;
		}
	}
	cap.release();
	destroyAllWindows();
}

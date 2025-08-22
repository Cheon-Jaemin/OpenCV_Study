#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
	Mat img_color = imread("apple.jpg", IMREAD_COLOR);

	//이미지의 높이와 너비를 가져옴
	//Mat객체에 영상(이미지)이 저장되어 있다면
	int height = img_color.rows;	//Mat::rows영상의 세로 픽셀(행, y)
	int width = img_color.cols;		//Mat::cols영상의 가로 픽셀(열, x)

	//그레이 스케일 이미지를 저장할 Mat객체를 생성
	Mat img_gray(height, width, CV_8UC1); //8비트 uchar, 채널 1개, 그레이 스케일

	//for문을 돌면서 (x,y)에 있는 픽셀을 하나씩 접근
	for (int y = 0; y < height; y++)
	{
		//속도 향상을 위해 y좌표를 사용하여 포인터 위치를 미리 계산
		uchar* pointer_Input = img_color.ptr<uchar>(y);
		uchar* pointer_output = img_gray.ptr<uchar>(y);

		for (int x = 0; x < width; x++)
		{
			//컬러 이미지의 (x,y)에 있는 픽셀의 bgr채널을 읽음
			//한 픽셀에 bgr 3개의 채널이 있기 때문에 x좌표에 3을 곱함
			//한번에 3개의 열 씩 이동
			//그레이 스케일 이미지를 접근할 경우에는 3을 곱할 필요가 없음(1채널이기 때문)
			uchar b = pointer_Input[x * 3 + 0];
			uchar g = pointer_Input[x * 3 + 1];
			uchar r = pointer_Input[x * 3 + 2];

			//(x,y)위치의 픽셀에 그레이 스케일 값이 저장됨
			//변환된 밝기 값을 저장할 이미지
			//BT.709에 명시된 비율을 사용하는 경우
			//사람의 눈은 녹색에 가장 민감, 파란색이 가장 덜 민감, 시각적으로 더 정확한 밝기 계산을 위해 가중평균을 사용
			pointer_output[x] = r * 0.2126 + g * 0.7152 + b * 0.0722;
		}
	}

	//결과 이미지에 컬러를 표시하기 위해 컬러 이미지로 변환
	Mat img_result;
	cvtColor(img_gray, img_result, COLOR_GRAY2BGR);	//오버로딩하여 사용됨cvtColor(color,gray,…), cvtColor(gray,color,…)
	
	//y범위가 150~200, x범위가 200~250인 영역의 픽셀을 초록색 픽셀로 변경
	for (int y = 300; y < 350; y++)
	{
		//y행의 시작주소값, 150행의 시작 주소값
		uchar* pointer_input = img_result.ptr<uchar>(y);
		for (int x = 420; x < 470; x++)
		{
			pointer_input[x * 3 + 0] = 0;
			pointer_input[x * 3 + 1] = 255;	//하나의 픽셀에 bgr이 들어가게 되고 그중 G에만 255값을 넣어줌
			pointer_input[x * 3 + 2] = 0;
		}
	}

	//원본 이미지와 결과 이미지가 보여짐
	imshow("color", img_color);
	imshow("result", img_result);
	
	waitKey(0);
}

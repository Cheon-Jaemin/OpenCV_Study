#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;int main(void){	Mat img_edge, img_result;
	Mat src = imread("houghlines.jpg", IMREAD_GRAYSCALE);
	Canny(src, img_edge, 50, 150);
	cvtColor(img_edge, img_result, COLOR_GRAY2BGR);
	//Vec<int,4>, 정수형 데이터 4개를 가지는 linesP를 선언함, (x1, y1, x2, y2)직선을 저장
	//linesP : 라인의 시작점과 끝점을 저장할 출력벡터
	vector<Vec4i> linesP; //x1,y1,x2,y2	// img_edge: 입력 에지 이미지 (8비트 단일 채널)
	// linesP: 검출된 선분들이 저장될 출력 벡터
	// 1: rho (로) 해상도. 픽셀 단위의 거리 해상도 1픽셀 간격으로 직선을 탐색
	// CV_PI / 180: theta (세타) 해상도. 라디안 단위의 각도 해상도, 1도 간격으로 직선을 탐색
	// 50: threshold (임계값). 교차점의 최소 개수, 이 값보다 많은 표(accumulator) 값을 가진 직선만 반환(선을 구성하는 최소 픽셀 수와 관련됨)
	// 50: minLineLength (최소 선 길이). 검출될 선분의 최소 길이, 이보다 짧은 선분은 무시
	// 3: maxLineGap (최대 선 간격). 같은 선으로 간주될 수 있는 선분 사이의 최대 간격
	// 이 간격 내의 두 선분은 하나의 선분으로 합쳐짐
	HoughLinesP(img_edge, linesP, 1, CV_PI / 180, 50, 40, 3);	// 확률적 허프 변환 (HoughLinesP)을 사용하여 선 검출
	// `HoughLinesP`는 이미지에서 선분을 찾음, 일반적인 `HoughLines`보다 더 효율적이고 실제 선분을 반환
	for (size_t i = 0; i < linesP.size(); i++)
	{
		Vec4i l = linesP[i]; // 검출된 선분들의 시작점과 끝점 좌표 (x1, y1, x2, y2)를 저장할 벡터
		// `line` 함수를 사용하여 'img_result' 이미지에 선분을 그림
		// Point(l[0], l[1]): 선분의 시작점 (x1, y1)
		// Point(l[2], l[3]): 선분의 끝점 (x2, y2)
		// Scalar(0, 0, 255): 선분의 색상 (BGR 순서: 파랑=0, 초록=0, 빨강=255 -> 빨간색 선)
		// 3: 선분의 두께 (픽셀)
		line(img_result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}
	imshow("Source", src);
	imshow("Probabilistic Line Transform", img_result);
	waitKey();
	return 0;}
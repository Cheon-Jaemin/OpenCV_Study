#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;vector<Point> detectedObjects;bool notInList(Point newObject)
{
	// detectedObjects 벡터에 저장된 모든 기존 객체들과 newObject의 거리를 계산
	for (int i = 0; i < detectedObjects.size(); i++)
	{
		float a = detectedObjects[i].x - newObject.x; // 두 점의 x 좌표 차이
		float b = detectedObjects[i].y - newObject.y; // 두 점의 y 좌표 차이
		// 유클리드 거리 계산 (두 점 사이의 직선 거리)
		if (sqrt(a * a + b * b) < 5.0)
		{
			return false; // 거리가 5.0 미만이면 이미 탐지된 객체와 매우 가까이 있다는 뜻이므로 중복으로 간주
		}
	}
	return true;
} // 모든 기존 객체들과의 거리가 5.0 이상이면 중복이 아니므로 새로운 객체로 간주

int main(void)
{
	Mat img_rgb = imread("blue.jpg");

	Mat img_gray;
	cvtColor(img_rgb, img_gray, COLOR_BGR2GRAY);

	Mat img_template = imread("template.jpg", IMREAD_GRAYSCALE);
	int w = img_template.cols;
	int h = img_template.rows;

	Mat result;
	matchTemplate(img_gray, img_template, result, TM_CCOEFF_NORMED);

	int count = 0;
	for (int x = 0; x < result.cols; x++)
	{
		for (int y = 0; y < result.rows; y++)
		{
			if (result.at<float>(y, x) > 0.9 && notInList(Point(x, y)))
			{
				detectedObjects.push_back(Point(x, y));
				rectangle(img_rgb, Point(x, y), Point(x + w, y + h), Scalar(0, 0, 255), 1);
				count++;
			}
		}
	}
	cout << "발견된 갯수" << count << endl;
	imshow("result", img_rgb);

	waitKey(0);
	return 0;
}

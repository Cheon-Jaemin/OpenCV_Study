#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(void)
{
	Mat img_color = imread("flower.jpg", IMREAD_COLOR);
	imshow("color", img_color);

	int height = img_color.rows;
	int width = img_color.cols;

	Mat M = getRotationMatrix2D(Point(width / 2.0, height / 2.0), 10, 1);
	Mat M1 = getRotationMatrix2D(Point(width / 2.0, height / 2.0), 20, 1);
	Mat M2 = getRotationMatrix2D(Point(width / 2.0, height / 2.0), 30, 1);
	Mat M3 = getRotationMatrix2D(Point(width / 2.0, height / 2.0), 45, 1);

	Mat img_rotated;
	Mat img_rotated1;
	Mat img_rotated2;
	Mat img_rotated3;

	warpAffine(img_color, img_rotated, M, Size(width, height));
	warpAffine(img_color, img_rotated1, M1, Size(width, height));
	warpAffine(img_color, img_rotated2, M2, Size(width, height));
	warpAffine(img_color, img_rotated3, M3, Size(width, height));

	imshow("roatation", img_rotated);
	imshow("roatation1", img_rotated1);
	imshow("roatation2", img_rotated2);
	imshow("roatation3", img_rotated3);

	waitKey(0);

	return 0;
}

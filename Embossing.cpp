#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(void)
{
	Mat src = imread("lena.png", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "이미지를 불러올 수 없음" << endl;
		return -1;
	}
	imshow("src", src);

	float data[] = { -1, -1, 0, -1, 0, 1, 0, 1, 1 };
	Mat emboss(3, 3, CV_32FC1, data);

	Mat dst;
	filter2D(src, dst, -1, emboss, Point(-1, -1), 128);

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}

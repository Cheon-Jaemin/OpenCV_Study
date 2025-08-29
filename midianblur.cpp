#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("lenanoise.png", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "이미지를 불러올 수 없음" << endl;
		return -1;
	}
	imshow("src", src);

	Mat img_blur;
	GaussianBlur(src, img_blur, Size(7, 7), 0);

	imshow("src", src);
	imshow("img_blur", img_blur);

	waitKey();
	destroyAllWindows();
}
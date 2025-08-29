#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
	Mat src = imread("lena1.jpg", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "이미지를 불러올 수 없음" << endl;
		return -1;
	}
	imshow("src", src);

	Mat noise(src.size(), CV_32SC1);

	randn(noise, 0, 5);
	add(src, noise, src, Mat(), CV_8U);

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);
	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey(0);
	destroyAllWindows();
}

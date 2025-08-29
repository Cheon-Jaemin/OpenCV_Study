#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("human1.png", IMREAD_GRAYSCALE);
	if (src.empty())
	{
		cout << "이미지를 불러올 수 없음" << endl;
		return -1;
	}

	Mat dst;
	threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat dst1, dst2;
	morphologyEx(dst, dst1, MORPH_OPEN, kernel);
	morphologyEx(dst, dst2, MORPH_CLOSE, kernel);

	imshow("src", src);
	imshow("dst", dst);
	imshow("Open", dst1);
	imshow("Close", dst2);

	waitKey(0);
	return 0;
	destroyAllWindows();
}
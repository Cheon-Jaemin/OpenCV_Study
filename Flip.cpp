#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("flower.jpg");
	if (src.empty())
	{
		cerr << "ÀÌ¹ÌÁö x" << endl;
		return -1;
	}
	imshow("src", src);

	Mat dst;
	int flipCode[] = { 1, 0, -1 };

	flip(src, dst, flipCode[0]);
	imshow("dst1", dst);
	flip(src, dst, flipCode[1]);
	imshow("dst2", dst);
	flip(src, dst, flipCode[2]);
	imshow("dst3", dst);
	
	waitKey(0);
	destroyAllWindows();
}

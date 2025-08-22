#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(void)
{
	Mat img_color = imread("flower.jpg", IMREAD_COLOR);
	imshow("color", img_color);

	int height = img_color.rows;
	int width = img_color.cols;

	int angle = 1;
	int angle2 = 1;

	while (1)
	{
		angle = angle + 2;
		angle2 = angle2 + 2;

		Mat M = getRotationMatrix2D(Point(width / 2.0, height / 2.0), angle, 1);
		Mat img_rotated;
		warpAffine(img_color, img_rotated, M, Size(width, height));

		Mat M2 = getRotationMatrix2D(Point(width / 2.0, height / 2.0), angle2, 1);
		Mat img_rotated2;
		warpAffine(img_color, img_rotated2, M2, Size(width, height));

		vector<Mat>mat = { img_rotated, img_rotated2 };
		Mat Chun_sum;
		hconcat(mat, Chun_sum);

		vector<Mat>mat2 = { img_rotated2, img_rotated };
		Mat Chun_sum2;
		hconcat(mat2, Chun_sum2);

		vector<Mat>mat_sum = { Chun_sum, Chun_sum2 };
		Mat chun_result;

		vconcat(mat_sum, chun_result);
		imshow("rotation", chun_result);
		waitKey(1);
	}
	return 0;
}

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
	Mat img(500, 600, CV_8UC3);

	RNG rng(543210);

	while (1)
	{
		for (int y = 0; y < 500; y++)
		{
			uchar* ptr = img.ptr<uchar>(y);
			for (int x = 0; x < 600; x++)
			{
				ptr[x * 3 + 0] = rng.uniform(0, 255);
				ptr[x * 3 + 1] = rng.uniform(0, 255);
				ptr[x * 3 + 2] = rng.uniform(0, 255);
			}
		}
		imshow("draw", img);

		if (waitKey(0) == 27)
		{
			break;
		}
	}
}

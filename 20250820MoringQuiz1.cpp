#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{
	Mat image_color = imread("cat on laptop.jpg", IMREAD_GRAYSCALE);
	imshow("original", image_color);

	Mat image_copyed1 = image_color;
	Mat image_copyed2 = image_color;
	
	threshold(image_color, image_color, 100, 255, THRESH_BINARY);
	imshow("image_color", image_color);
	imshow("image_copyed1", image_copyed1);
	imshow("image_copyed2", image_copyed2);
	
	waitKey(0);
}

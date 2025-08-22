#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
	Mat img_color;
	img_color = imread("cat on laptop.jpg", IMREAD_GRAYSCALE);
	
	//clone 함수를 사용하여 Mat객체 img_color의 복사본을 만듦, 깊은복사
	Mat img_copyed1 = img_color.clone(); //복제방법1
	Mat img_copyed2;
	
	//copyTo함수를 사용하여 Mat객체 img_color의 복사본을 만듦
	img_color.copyTo(img_copyed2); //복제방법2
	
	//하나의 Mat객체에 이진화를 적용해봄
	threshold(img_color, img_color, 127, 255, THRESH_BINARY);
	imshow("img_color", img_color); //첫번째 이미지만 이진화 되고 다른 이미지는 변화하지 않음
	imshow("img_copyed1", img_copyed1); //clone()을 사용한 깊은 복사가 이루어져 복사본과 원본의 참조주소가 달름
	imshow("img_copyed2", img_copyed2);

	waitKey(0);
}
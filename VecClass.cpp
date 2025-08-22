#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main(void)
{
	Vec3f vec(1.0f, 2.0f, 3.0f);
	cout << "Vec3f : " << vec << endl;

	float x = vec[0];
	float y = vec[1];
	float z = vec[2];

	cout << "x : " << x << ", y : " << y << ", z : " << z << endl;

	return;
}

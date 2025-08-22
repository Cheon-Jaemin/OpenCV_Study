#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main(void)
{
	Rect_<int> rect1(0, 0, 100, 1000);
	Rect_<float> rect2(Point2f(0.f, 0.f), Point2f(120.5f, 103.5f));
	Rect_<double> rect3(Point2d(0., 0.), Size2d(100.2, 200.));

	Rect2i rect4(10, 20, 30, 40);
	Rect2f rect5(50.f, 60.f, 70.f, 80.f);
	Rect2d rect6(100., 200., 300., 400.);
	
	Rect rect7(0, 10, 20, 30);

	cout << "rect1 ���� ���� �� : " << rect1.tl() << endl;
	cout << "rect1 ������ �Ʒ��� �� : " << rect1.br() << endl;
	cout << "rect1 ���μ��� ������ : " << rect1.size() << endl;
	cout << "rect1 ������ ���� : " << rect1.area() << endl;
	cout << "rect1�� ��ǥ�� �����ϴ��� üũ : " << rect1.contains(Point(50, 50)) << endl;
	cout << "\n" << endl;
	
	cout << "rect2 ���� ���� �� : " << rect2.tl() << endl;
	cout << "rect2 ������ �Ʒ��� �� : " << rect2.br() << endl;
	cout << "rect2 ���μ��� ������ : " << rect2.size() << endl;
	cout << "rect2 ������ ���� : " << rect2.area() << endl;
	cout << "rect2�� ��ǥ�� �����ϴ��� üũ : " << rect2.contains(Point(50, 50)) << endl;
	cout << "\n" << endl;

	Rect rect8 = rect4 + Size(50, 40);
	cout << "rect8 ���μ��� ������ : " << rect8.size() << endl;
	cout << "\n" << endl;

	Rect rect9 = rect7 + Point(10, 10);
	cout << "rect9�� ��ǥ �̵� : " << rect9.tl() << endl;
	cout << "\n" << endl;

	Rect rect10 = rect4 & rect7;
	cout << "rect10 ���� ���� �� : " << rect10.tl() << endl;
	cout << "rect10 ������ �Ʒ��� �� : " << rect10.br() << endl;
	cout << "\n" << endl;

	cout << "rect10 " << rect10 << endl;
}
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;int main(void){	Mat img_edge, img_result;
	Mat src = imread("houghlines.jpg", IMREAD_GRAYSCALE);
	Canny(src, img_edge, 50, 150);
	cvtColor(img_edge, img_result, COLOR_GRAY2BGR);
	//Vec<int,4>, ������ ������ 4���� ������ linesP�� ������, (x1, y1, x2, y2)������ ����
	//linesP : ������ �������� ������ ������ ��º���
	vector<Vec4i> linesP; //x1,y1,x2,y2	// img_edge: �Է� ���� �̹��� (8��Ʈ ���� ä��)
	// linesP: ����� ���е��� ����� ��� ����
	// 1: rho (��) �ػ�. �ȼ� ������ �Ÿ� �ػ� 1�ȼ� �������� ������ Ž��
	// CV_PI / 180: theta (��Ÿ) �ػ�. ���� ������ ���� �ػ�, 1�� �������� ������ Ž��
	// 50: threshold (�Ӱ谪). �������� �ּ� ����, �� ������ ���� ǥ(accumulator) ���� ���� ������ ��ȯ(���� �����ϴ� �ּ� �ȼ� ���� ���õ�)
	// 50: minLineLength (�ּ� �� ����). ����� ������ �ּ� ����, �̺��� ª�� ������ ����
	// 3: maxLineGap (�ִ� �� ����). ���� ������ ���ֵ� �� �ִ� ���� ������ �ִ� ����
	// �� ���� ���� �� ������ �ϳ��� �������� ������
	HoughLinesP(img_edge, linesP, 1, CV_PI / 180, 50, 40, 3);	// Ȯ���� ���� ��ȯ (HoughLinesP)�� ����Ͽ� �� ����
	// `HoughLinesP`�� �̹������� ������ ã��, �Ϲ����� `HoughLines`���� �� ȿ�����̰� ���� ������ ��ȯ
	for (size_t i = 0; i < linesP.size(); i++)
	{
		Vec4i l = linesP[i]; // ����� ���е��� �������� ���� ��ǥ (x1, y1, x2, y2)�� ������ ����
		// `line` �Լ��� ����Ͽ� 'img_result' �̹����� ������ �׸�
		// Point(l[0], l[1]): ������ ������ (x1, y1)
		// Point(l[2], l[3]): ������ ���� (x2, y2)
		// Scalar(0, 0, 255): ������ ���� (BGR ����: �Ķ�=0, �ʷ�=0, ����=255 -> ������ ��)
		// 3: ������ �β� (�ȼ�)
		line(img_result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}
	imshow("Source", src);
	imshow("Probabilistic Line Transform", img_result);
	waitKey();
	return 0;}
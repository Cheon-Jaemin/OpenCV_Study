#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{

	VideoCapture cap(0, CAP_DSHOW);
	if (!cap.isOpened())
	{
		cout << "카메라를 열 수 없습니다." << endl;
		return -1;
	}
	Mat src;
	while (1)
	{
		bool ret = cap.read(src);
		if (!ret)
		{
			cout << "캡쳐 실패" << endl;
			break;
		}
		if (src.empty())
		{
			cout << "이미지 파일을 읽을 수 없습니다." << endl;
			return -1;
		}
		vector<Mat> bgr_planes;
		split(src, bgr_planes);
		
		//픽셀값의 범위는 0~255이므로 전체 개수는 256개로 선언
		int histSize = 256;
		
		//픽셀값의 범위는 0~255, 상위 경계인 256은 포함되지 않음
		float range[] = { 0, 256 };
		const float* histRange = { range };
		
		//히스토그램 막대 크기가 똑같고 처음 시작 시 히스토그램이 비어있도록 함
		bool uniform = true, accumulate = false;
		
		//BGR채널로 히스토그램을 계산
		Mat b_hist, g_hist, r_hist;
		calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
		calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
		calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
		
		//히스토그램을 보여줄 이미지를 생성
		int hist_w = 256 * 3, hist_h = 400;
		Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
		
		//값들이 영상을 벗어나지 않도록 히스토그램을 정규화함
		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		
		//히스토그램을 그려줌
		for (int i = 0; i < histSize; i++)
		{//파란색 히스토그램
			line(histImage, Point(i, hist_h - cvRound(b_hist.at<float>(i))), Point(i, hist_h - 0), Scalar(255, 0, 0), 2);
			//녹색 히스토그램
			line(histImage, Point(i + 256, hist_h - cvRound(g_hist.at<float>(i))), Point(i + 256, hist_h - 0), Scalar(0, 255, 0), 2);
			//빨간색 히스토그램
			line(histImage, Point(i + 256 * 2, hist_h - cvRound(r_hist.at<float>(i))), Point(i + 256 * 2, hist_h - 0), Scalar(0, 0, 255), 2);
		}
		imshow("Source image", src);
		imshow("Histogram", histImage);
		if (waitKey(1) == 27)
			break;
	}
	return EXIT_SUCCESS;
}

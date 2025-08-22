#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat img_color;
	img_color = imread("color.png", IMREAD_COLOR); 
	//BGR의 3개 채널이 결합된 Multi-channel
	//컬러 이미지를 채널별로 분리
	//img_channels배열에 blue, green, red순으로 채널이 저장됨
	
	Mat img_channels[3]; 
	//split(분리)해서 3개의 채널을 담을 배열 선언
	//void split(const Mat&src, Mat dest[ ]), 첫번째 매개변수는 분리할 영상, 두번째 매개변수는 분리된 채널들이 저장될 배열
	
	split(img_color, img_channels); 
	//b->0번째 요소, g->1번째 요소, R->2번째 요소로 분리
	//배열이름 img_channels만 쓰면 0번째 주소가 전달됨
	//채널별 이미지를 조합하여 컬러 영상을 생성함
	//blue와 red의 순서를 바꾸기 위해 push_back()사용
	
	vector<Mat> channels;
	channels.push_back(img_channels[2]); // 2번째 인텍스뒤에 1번째 인덱스를 그 뒤에 0번째 인덱스를 연결함
	channels.push_back(img_channels[1]);
	channels.push_back(img_channels[0]);
	
	Mat img_result;
	//void merge(Vector<Mat> src, Mat dest), 첫번째 매개변수 입력 영상의 벡터값, 두번째 매개변수 출력영상
	//채널 병합, 1개 채널 영상 N개를 N채널 영상 1개로 병합
	merge(channels, img_result);
	
	imshow("Color", img_result);
	imshow("B", img_channels[0]);
	imshow("G", img_channels[1]);
	imshow("R", img_channels[2]);
	waitKey(0);
	return 0;
}
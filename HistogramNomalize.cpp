#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat draw_histogram(Mat img)
{
    int hist_h = img.rows;
    int hist_w = 256;
    Mat img_histogram1(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

    Mat hist_item;
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;

    calcHist(&img, 1, 0, Mat(), hist_item, 1, &histSize, &histRange, uniform, accumulate);
    normalize(hist_item, hist_item, 0, 255, NORM_MINMAX);

    for (int i = 1; i < histSize; i++)
    {
        line(img_histogram1, Point(i, hist_h - cvRound(hist_item.at<float>(i))), Point(i, hist_h), Scalar(255, 255, 255));
    }

    Mat img_histogram2(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

    Mat c_hist(hist_item.size(), hist_item.type());
    c_hist.at<float>(0) = hist_item.at<float>(0);

    for (int i = 1; i < hist_item.rows; i++)
    {
        c_hist.at<float>(i) = hist_item.at<float>(i) + c_hist.at<float>(i - 1);
    }

    normalize(c_hist, c_hist, 0, 255, NORM_MINMAX);

    vector<Point> contour;
    for (int i = 1; i < histSize; i++)
    {
        contour.clear();
        contour.push_back(Point(i, hist_h - cvRound(c_hist.at<float>(i))));
        contour.push_back(Point((i - 1), hist_h - cvRound(c_hist.at<float>(i - 1))));

        const Point* pts = (const cv::Point*)Mat(contour).data;

        int npts = Mat(contour).rows;

        for (int i = 1; i < histSize; i++)
        {
            line(img_histogram2, Point(i - 1, hist_h - cvRound(c_hist.at<float>(i - 1))), Point(i, hist_h - cvRound(c_hist.at<float>(i))), Scalar(255, 255, 255));
        }
    }
    Mat result;
    hconcat(img_histogram1, img_histogram2, result);
    return result;
}

int main()
{
    VideoCapture cap(0, CAP_DSHOW);
    if (!cap.isOpened())
    {
        cout << "카메라를 열 수 없습니다." << endl;
        return -1;
    }
    Mat img_color;
    while (1)
    {
        bool ret = cap.read(img_color);
        if (!ret)
        {
            cout << "캡쳐 실패" << endl;
            break;
        }
        if (img_color.empty())
        {
            cout << "이미지 파일을 읽을 수 없습니다." << endl;
            return -1;
        }

        Mat img_gray;
        cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

        //원본이미지에 대한 히스토그램을 그림
        Mat img_histo1 = draw_histogram(img_gray);
        Mat result1;
        hconcat(img_gray, img_histo1, result1);
        imshow("source", result1);

        //히스토그램 평활화를 적용 후 히스토그램을 그림
        Mat img_equ;

        //히스토그램정보를 통해서 입력이미지를 균일화 해준 후 결과이미지에 저장
        equalizeHist(img_gray, img_equ);
        Mat img_histo2 = draw_histogram(img_equ);
        Mat result2;
        hconcat(img_equ, img_histo2, result2);
        imshow("result2", result2);


        if (waitKey(1) == 27)
        {
            break;
        }
    }
    return 0;
}
#include "car.h"


//����ͼ��  
Mat img;
//�Ҷ�ֵ��һ��  
Mat bgr;
//HSVͼ��  
Mat hsv;
//ɫ��  
int hmin = 0;
int hmin_Max = 360;
int hmax = 360;
int hmax_Max = 360;
//���Ͷ�  
int smin = 0;
int smin_Max = 255;
int smax = 255;
int smax_Max = 255;
//����  
int vmin = 106;
int vmin_Max = 255;
int vmax = 250;
int vmax_Max = 255;
//��ʾԭͼ�Ĵ���  
string windowName = "src";
//���ͼ�����ʾ����  
string dstName = "dst";
//���ͼ��  
Mat dst;
//�ص�����  
void callBack(int, void*)
{
	//���ͼ������ڴ�  
	dst = Mat::zeros(img.size(), CV_32FC3);
	//����  
	Mat mask;
	inRange(hsv, Scalar(hmin, smin / float(smin_Max), vmin / float(vmin_Max)), Scalar(hmax, smax / float(smax_Max), vmax / float(vmax_Max)), mask);
	//ֻ����  
	for (int r = 0; r < bgr.rows; r++)
	{
		for (int c = 0; c < bgr.cols; c++)
		{
			if (mask.at<uchar>(r, c) == 255)
			{
				dst.at<Vec3f>(r, c) = bgr.at<Vec3f>(r, c);
			}
		}
	}
	//���ͼ��  
	imshow(dstName, dst);
	//����ͼ��  
	dst.convertTo(dst, CV_8UC3, 255.0, 0);
	imwrite("HSV_inRange.jpg", dst);
}
void test_main()
{
	//����ͼ��  
	img = imread("E:\\�ز�ͼƬ\\1.png",1);
	if (!img.data || img.channels() != 3)
		return ;
	imshow(windowName, img);
	//��ɫͼ��ĻҶ�ֵ��һ��  
	img.convertTo(bgr, CV_32FC3, 1.0 / 255, 0);
	//��ɫ�ռ�ת��  
	cvtColor(bgr, hsv, COLOR_BGR2HSV);
	//�������ͼ�����ʾ����  
	namedWindow(dstName, WINDOW_NORMAL);
	//����ɫ�� H  
	createTrackbar("hmin", dstName, &hmin, hmin_Max, callBack);
	createTrackbar("hmax", dstName, &hmax, hmax_Max, callBack);
	//���ڱ��Ͷ� S  
	createTrackbar("smin", dstName, &smin, smin_Max, callBack);
	createTrackbar("smax", dstName, &smax, smax_Max, callBack);
	//�������� V  
	createTrackbar("vmin", dstName, &vmin, vmin_Max, callBack);
	createTrackbar("vmax", dstName, &vmax, vmax_Max, callBack);
	callBack(0, 0);
	waitKey(0);
	return;
}
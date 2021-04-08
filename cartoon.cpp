#include"opencv2/opencv.hpp"
#include "cartoon.h"
using namespace cv;
using namespace std;

void cartoonifyImage(const Mat &srcColor, Mat &dst)
{
	Mat gray;
	cvtColor(srcColor, gray, COLOR_BGR2GRAY);
	const int MEDIAN_BLUR_FILTER_SIZE = 7;
	medianBlur(gray, gray, MEDIAN_BLUR_FILTER_SIZE);
	Mat edges;
	const int LAPLACIAN_FILTER_SIZE = 5;
	Laplacian(gray, edges, CV_8U, LAPLACIAN_FILTER_SIZE);

	Mat mask;
	const int EDGES_THRESHOLD = 80;
	threshold(edges, mask, EDGES_THRESHOLD, 255, THRESH_BINARY_INV);

	Size size = srcColor.size();
	Size smallSize;
	smallSize.width = size.width / 2;
	smallSize.height = size.height / 2;
	Mat smallImg = Mat(smallSize, CV_8UC3);

	resize(srcColor, smallImg, smallSize, 0, 0, INTER_LINEAR);

	Mat tmp = Mat(smallSize, CV_8UC3);
	int repetitions = 7;//repetition for strong cartoon effect

	for (int i = 0; i < repetitions; i++) {
		int ksize = 9;   //filter size
		double sigmaColor = 9;//filter color strength
		double sigmaSpace = 7;//spatial strength 
		bilateralFilter(smallImg, tmp, ksize, sigmaColor, sigmaSpace);
		bilateralFilter(tmp, smallImg, ksize, sigmaColor, sigmaSpace);
	}
	
	Mat bigImg;
	resize(smallImg, bigImg, size, 0, 0, INTER_LINEAR);
	dst.setTo(0);
	bigImg.copyTo(dst, mask);
}
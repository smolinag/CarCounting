#ifndef ForegroundPostProcessing_H
#define ForegroundPostProcessing_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include "Definitions.h"

using cv::Mat;
using cv::Point;
using cv::Scalar;
using std::vector;

class ForegroundPostProcessing{

public:
	ForegroundPostProcessing();

	ForegroundPostProcessing(const Mat iniFrame);

	void postProcessingMain(const Mat &fMask);

	void fillHoles(const Mat &fMask);

	void deleteSmallRegions(const Mat &fMask);

	int roiLabelling(Mat fMask, Mat &bwFMask);

	void imagesc(Mat src, int siz, char* Plotname);

	vector<vector<Point>> roisCountours;	

	Mat fMaskPost;	//Foreground mask after postprocessing

	Mat labeledRoisMask;

	int nRois;

private:

	Mat morphElement;
	int minArea;
	vector<vector<Point>> contours;
	vector<cv::Vec4i> hierarchy;
	Point pt;
};
#endif
#ifndef ForegroundPostProcessing_H
#define ForegroundPostProcessing_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>

using cv::Mat;
using cv::Point;
using cv::Scalar;
using std::vector;

class ForegroundPostProcessing{

public:
	ForegroundPostProcessing();

	void postProcessingMain(const Mat &fMask);

	void fillHoles(const Mat &fMask);

	void deleteSmallRegions(const Mat &fMask);

	vector<vector<Point>> roisCountours;	

	Mat fMaskPost;	//Foreground mask after postprocessing

	Mat labeledRoisMask;

	int nRois;

private:

	int morphSize1;
	int morphSize2;
	Mat morphElement1;
	Mat morphElement2;
	int minArea;
	vector<vector<Point>> contours;
	vector<cv::Vec4i> hierarchy;
	Point pt;
};
#endif
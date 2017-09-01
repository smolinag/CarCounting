#ifndef ForegroundPostProcessing_H
#define ForegroundPostProcessing_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>

class ForegroundPostProcessing{

public:
	ForegroundPostProcessing(const cv::Mat iniFrame);

	void postProcessingMain(const cv::Mat &fMask);

	void fillHoles(const cv::Mat &fMask);

	void deleteSmallRegions(const cv::Mat &fMask);

	int roiLabelling(cv::Mat fMask, cv::Mat &bwFMask);

	void imagesc(cv::Mat src, int siz, char* Plotname);

	std::vector<std::vector<cv::Point>> roisCountours;	

	cv::Mat fMaskPost;

	int nRois;

private:

	int morphSize1;
	int morphSize2;
	cv::Mat morphElement1;
	cv::Mat morphElement2;
	int minArea;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::Point pt;
};
#endif
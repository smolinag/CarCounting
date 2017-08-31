#ifndef ForegroundPostProcessing_H
#define ForegroundPostProcessing_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>

//Color library
const static uchar Color[20][3] = { { 200, 0, 0 }, { 0, 0, 200 }, { 0, 200, 0 }, { 200, 200, 0 }, { 0, 200, 200 }, { 200, 0, 200 },
{ 0, 80, 255 }, { 220, 150, 200 }, { 0, 250, 100 }, { 100, 0, 250 }, { 100, 250, 0 }, { 240, 240, 100 }, { 180, 250, 20 }, { 160, 190, 20 },
{ 25, 255, 155 }, { 180, 130, 70 }, { 32, 165, 220 }, { 120, 150, 255 }, { 125, 25, 25 }, { 105, 180, 180 } };

class ForegroundPostProcessing{

public:
	ForegroundPostProcessing(const cv::Mat iniFrame);

	void postProcessingMain(const cv::Mat &fMask);

	void fillHoles();

	void deleteSmallRegions();

	int bwLabel(cv::Mat fMask, cv::Mat &bwFMask);

	void imagesc(cv::Mat src, int siz, char* Plotname);

	std::vector<std::vector<int>> xCoordRoiCountour;			//X coordinates of countours of each isolated region 
	std::vector<std::vector<int>> yCoordRoiCountour;			//Y coordinates of countours of each isolated region 

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
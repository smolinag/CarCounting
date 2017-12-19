#ifndef ForegroundObject_H
#define ForegroundObject_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include "Definitions.h"

class ForegroundObject{

public:
	ForegroundObject();

	ForegroundObject(std::vector<cv::Point> roiContour, int roiId);

	int id;
	cv::Point centroid;
	cv::Point botLeftCoord;
	int width;
	int height;
	int label;
	cv::Scalar color;
	std::vector<cv::Point> contour;
	std::vector<float> keyShapeFeatures;

private:

	void getStatesFromContour(std::vector<cv::Point> roiContour);
};
#endif
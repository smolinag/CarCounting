#ifndef TrackedObject_H
#define TrackedObject_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>

class TrackedObject{

public:
	TrackedObject();

	TrackedObject(std::vector<cv::Point> roiContour, int roiId);

	int id;
	cv::Point centroid;
	cv::Point botLeftCoord;
	int width;
	int height;
	int label;
	cv::Scalar color;

private:

	void getStatesFromContour(std::vector<cv::Point> roiContour);
};
#endif
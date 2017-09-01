#ifndef Tracking_H
#define Tracking_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include "TrackedObject.h"

class Tracking{

public:
	Tracking();

	void getCurrentFrameObjects(int nRois, cv::Mat fRois, std::vector<std::vector<cv::Point>> roisContours, cv::Mat frame);

	std::vector<TrackedObject> trackedObjects;

private:

	void showTrackingBBoxes(std::vector<TrackedObject>);

	cv::Mat frame;
	cv::Mat fRois;
	std::vector<std::vector<cv::Point>> roisContours;
	int trckingId;	
	std::vector<TrackedObject> detectedObjects;
};
#endif
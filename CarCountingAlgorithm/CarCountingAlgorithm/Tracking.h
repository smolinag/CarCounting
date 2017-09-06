#ifndef Tracking_H
#define Tracking_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include <numeric>
#include "TrackedObject.h"

class Tracking{

public:
	Tracking();

	void getCurrentFrameObjects(int nRois, cv::Mat fRois, std::vector<std::vector<cv::Point>> roisContours, cv::Mat frame);

	std::vector<TrackedObject> trackedObjects;

private:

	void showTrackingBBoxes(std::vector<TrackedObject> objects);

	void getNearestRois();

	std::vector<std::size_t> sortVectorGetIndexes(std::vector<double> vecA);

	cv::Mat frame;
	cv::Mat fRois;
	std::vector<std::vector<cv::Point>> roisContours;
	int trckingId;	
	std::vector<TrackedObject> detectedObjects;
	std::vector<std::vector<std::size_t>> nearestRoisRank;
};
#endif
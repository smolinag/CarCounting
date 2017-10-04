#ifndef Tracking_H
#define Tracking_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include <numeric>
#include "TrackedObject.h"

using cv::Scalar;
using cv::Point;
using cv::Mat;

using std::string;
using std::vector;
using std::size_t;

struct Lane{
	int id;
	Point directionP1;
	Point directionP2;
	vector<Point> polygonPoints;
	Mat mask;
};

class Tracking{

public:
	Tracking();

	Tracking(vector<Lane> lanesConfigInfo);

	void getCurrentFrameObjects(int numRois, Mat fRois, vector<vector<Point>> roisContours, Mat frame);

	vector<TrackedObject> trackedObjects;

private:

	bool checkRoiInsideLane(TrackedObject tObj, size_t roiIdx);

	void getNearestRois();

	void showTrackingBBoxes(vector<TrackedObject> objects);

	vector<std::size_t> sortVectorGetIndexes(vector<double> vecA);

	Mat frame;
	Mat labeledRoisMask;
	vector<vector<Point>> roisContours;
	int trckingId;	
	vector<TrackedObject> detectedObjects;
	vector<vector<std::size_t>> nearestRoisRank;
	vector<Lane> lanesInfo;
	int nRois;
};
#endif
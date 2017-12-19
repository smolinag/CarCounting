#ifndef ObjectTracker_H
#define ObjectTracker_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include <numeric>
#include "ForegroundObject.h"
#include "FeatureExtractor.h"
#include "ObjectClassifier.h"

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

class ObjectTracker{

public:
	ObjectTracker();

	ObjectTracker(vector<Lane> lanesConfigInfo, FeatureExtractor &fe, ObjectClassifier &oc);	

	void trackingProcess(Mat fRois, vector<vector<Point>> roisContours, Mat frame);

	vector<ForegroundObject> trackedObjects;

private:

	void getCurrentFrameObjects();

	bool checkRoiInsideLane(ForegroundObject tObj, size_t roiIdx);

	bool checkRoiIsVehicle(ForegroundObject tObj);

	void getNearestRois();

	void showTrackingBBoxes(vector<ForegroundObject> objects);

	vector<std::size_t> sortVectorGetIndexes(vector<double> vecA);

	FeatureExtractor featureExtractor;
	ObjectClassifier objectClassifier;
	vector<Lane> lanesInfo;

	int nRois;
	Mat frame;
	Mat labeledRoisMask;
	vector<vector<Point>> roisContours;

	int trckingId;	
	vector<ForegroundObject> detectedObjects;
	vector<vector<std::size_t>> nearestRoisRank;
	
};
#endif
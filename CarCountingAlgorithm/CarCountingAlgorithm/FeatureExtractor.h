#ifndef FEATUREEXTRACTION_H
#define FEATUREEXTRACTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "TrackedObject.h"
#include "Definitions.h"
#include <math.h>

using cv::Mat;
using cv::Point;
using cv::Scalar;
using std::vector;

class FeatureExtractor{

public:
	FeatureExtractor();

	void getShapeFeatures(vector<TrackedObject> &detectedObjects);

private:
	void getAngleAndMagnitude(TrackedObject detectedObject, Point cPoint, float &angle, float &magnitude);
};
#endif FEATUREEXTRACTION_H;
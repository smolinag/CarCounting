#ifndef FEATUREEXTRACTION_H
#define FEATUREEXTRACTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "ForegroundObject.h"
#include "Definitions.h"
#include <math.h>

using cv::Mat;
using cv::Point;
using cv::Scalar;
using std::vector;

class FeatureExtractor{

public:
	FeatureExtractor();

	void getShapeFeatures(ForegroundObject &detectedObject);

private:
	void getAngleAndMagnitude(ForegroundObject detectedObject, Point cPoint, float &angle, float &magnitude);
};
#endif FEATUREEXTRACTION_H;
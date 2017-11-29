#ifndef FEATUREEXTRACTION_H
#define FEATUREEXTRACTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using cv::Mat;
using cv::Point;
using cv::Scalar;
using std::vector;

class FeatureExtractor{

public:
	FeatureExtractor();

	void getShapeFeatures(vector<vector<Point>> roisContours, vector<vector<Point>> &keyShapePoints);

};
#endif FEATUREEXTRACTION_H;
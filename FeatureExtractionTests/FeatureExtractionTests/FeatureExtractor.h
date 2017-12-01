#ifndef FEATUREEXTRACTOR_H
#define FEATUREEXTRACTOR_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.141592

using namespace cv;
using namespace std;

class FeatureExtractor {

public:
	FeatureExtractor();

	void getShapeFeatures(vector<Point> objContour, vector<float> &shapeFeatures, vector<Point> &keyPoints, Mat im);

	void drawKeyPoints(Mat &img, const vector<Point> keyShapePoints);

private:
	float angleStep;	
};
#endif;
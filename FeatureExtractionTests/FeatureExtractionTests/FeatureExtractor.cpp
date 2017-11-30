#include "FeatureExtractor.h"

FeatureExtractor::FeatureExtractor(){
	angleStep = 15;	
}

void FeatureExtractor::getShapeFeatures(vector<Point> objContour, vector<Point> &keyPoints, Mat im) {

	vector<float> angleMinDifs = vector<float>(360 / angleStep, 999);
	vector<Point> keyShapePoints = vector<Point>(360 / angleStep, Point());

	//Find centroid
	int minX = 9999;
	int maxX = 0;
	int minY = 9999;
	int maxY = 0;
	for each(Point p in objContour) {
		if (p.x > maxX) {
			maxX = p.x;
		}
		if (p.x < minX) {
			minX = p.x;
		}
		if (p.y > maxY) {
			maxY = p.y;
		}
		if (p.y < minY) {
			minY = p.y;
		}
	}	
	int width = maxX - minX;
	int height = maxY - minY;
	Point centroid;
	centroid.x = minX + int(floor(double(width) / 2.));
	centroid.y = minY + int(floor(double(height) / 2.));

	//Find keyPoints
	float angle;
	float magnitude;
	float dx, dy;
	float angleDif;
	int nearestAngle;

	for each(Point p in objContour) {
		dx = p.x - centroid.x;
		dy = (im.rows - p.y) - (im.rows - centroid.y);
		angle = atan2(dy, dx) * 180 / PI;
		angle = fmod(angle + 360 , 360);
		magnitude = sqrt((dx * dx) + (dy * dy));
		
		angleDif = fmod(angle, angleStep);
		nearestAngle = (int)floor(angle / angleStep);

		/*cout << "p:" << p << " a:" << angle << " ad:" << angleDif << " na:" << nearestAngle << endl;
		circle(im, p, 2, Scalar(0, 20, 255), 2);
		circle(im, centroid, 2, Scalar(255, 20, 0), 2);
		imshow("test", im);
		waitKey();*/

		if (angleDif < angleMinDifs[nearestAngle]) {
			keyShapePoints[nearestAngle] = p;
			angleMinDifs[nearestAngle] = angleDif;
		}		
	}

	keyPoints = keyShapePoints;
}

void FeatureExtractor::drawKeyPoints(Mat &img, const vector<Point> keyShapePoints) {

	for each(Point p in keyShapePoints) {
		circle(img, p, 2, Scalar(0, 20, 255), 2);
	}
}
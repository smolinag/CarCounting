#include "FeatureExtractor.h"

FeatureExtractor::FeatureExtractor(){
	angleStep = 15;
	angleMinDifs = vector<float>(360 / angleStep, 999);
}

void FeatureExtractor::getShapeFeatures(vector<Point> objContour, vector<Point> &keyShapePoints) {

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
	bool angleFound = false;
	for each(Point p in objContour) {
		dx = centroid.x - p.x;
		dy = centroid.y - p.y;
		angle = atan2(dy, dx) * 180 / PI;
		magnitude = sqrt((dx * dx) + (dy * dy));
		
		angleDif = fmod(angle, angleStep);
		nearestAngle
		if ((angleDif < minAngleDif) && !angleFound) {
			angleFound = true;
			keyShapePoints.push_back(p);
		}
		else {
			angleFound = false;
		}
	}
}

void FeatureExtractor::drawKeyPoints(Mat &img, const vector<Point> keyShapePoints) {

	for each(Point p in keyShapePoints) {
		circle(img, p, 2, Scalar(0, 20, 255), 2);
	}
}
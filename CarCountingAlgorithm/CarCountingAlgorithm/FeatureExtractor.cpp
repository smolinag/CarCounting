#include "FeatureExtractor.h"

FeatureExtractor::FeatureExtractor(){}

void FeatureExtractor::getShapeFeatures(vector<TrackedObject> detectedObjects, vector<vector<Point>> &keyShapePoints){

	float angle, magnitude;
	float angleStep = SHAPE_ANGLE_STEP;
	float angleThr = SHAPE_ANGLE_THR;

	for each  (TrackedObject object in detectedObjects){
		for each (Point cPoint in object.contour){
			getAngleAndMagnitude(object.centroid, cPoint, angle, magnitude);

			if (fmod(angle, angleStep) < angleThr){

			}
		}
	}
}

void FeatureExtractor::getAngleAndMagnitude(Point centroid, Point cPoint, float &angle, float &magnitude){

	float dx = centroid.x - cPoint.x;
	float dy = centroid.y - cPoint.y;
	angle = atan2(dy, dx);
	magnitude = sqrt((dx * dx) + (dy * dy));

}
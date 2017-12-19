#include "FeatureExtractor.h"

FeatureExtractor::FeatureExtractor(){}

void FeatureExtractor::getShapeFeatures(ForegroundObject &detectedObject){

	vector<float> angleMinDifs = vector<float>(360 / SHAPE_ANGLE_STEP, 999);
	float angle, magnitude;
	float angleDif, nearestAngle;

	detectedObject.keyShapeFeatures = vector<float>(360 / SHAPE_ANGLE_STEP);
	for each (Point cPoint in detectedObject.contour) {
		getAngleAndMagnitude(detectedObject, cPoint, angle, magnitude);

		angleDif = fmod(angle, SHAPE_ANGLE_STEP);
		nearestAngle = (int)floor(angle / SHAPE_ANGLE_STEP);

		if (angleDif < angleMinDifs[nearestAngle]) {
			detectedObject.keyShapeFeatures[nearestAngle] = magnitude;
			angleMinDifs[nearestAngle] = angleDif;
		}
	}
}

void FeatureExtractor::getAngleAndMagnitude(ForegroundObject detectedObject, Point cPoint, float &angle, float &magnitude){

	float dx = cPoint.x - detectedObject.centroid.x;
	float dy = (detectedObject.height - cPoint.y) - (detectedObject.height - detectedObject.centroid.y);
	angle = atan2(dy, dx) * 180 / PI;
	angle = fmod(angle + 360, 360);
	magnitude = sqrt((dx * dx) + (dy * dy));
}
#include "FeatureExtractor.h"

FeatureExtractor::FeatureExtractor(){}

void FeatureExtractor::getShapeFeatures(vector<TrackedObject> &detectedObjects){

	vector<float> angleMinDifs = vector<float>(360 / SHAPE_ANGLE_STEP, 999);
	float angle, magnitude;	
	float angleDif, nearestAngle;

	for each  (TrackedObject &object in detectedObjects){
		object.keyShapeFeatures = vector<float>(360 / SHAPE_ANGLE_STEP);
		for each (Point cPoint in object.contour){
			getAngleAndMagnitude(object, cPoint, angle, magnitude);

			angleDif = fmod(angle, SHAPE_ANGLE_STEP);
			nearestAngle = (int)floor(angle / SHAPE_ANGLE_STEP);

			if (angleDif < angleMinDifs[nearestAngle]) {
				object.keyShapeFeatures[nearestAngle] = magnitude;
				angleMinDifs[nearestAngle] = angleDif;
			}
		}
	}
}

void FeatureExtractor::getAngleAndMagnitude(TrackedObject detectedObject, Point cPoint, float &angle, float &magnitude){

	float dx = cPoint.x - detectedObject.centroid.x;
	float dy = (detectedObject.height - cPoint.y) - (detectedObject.height - detectedObject.centroid.y);
	angle = atan2(dy, dx) * 180 / PI;
	angle = fmod(angle + 360, 360);
	magnitude = sqrt((dx * dx) + (dy * dy));
}
#include "ObjectTracker.h"

ObjectTracker::ObjectTracker(){

}

ObjectTracker::ObjectTracker(vector<Lane> lanesConfigInfo, FeatureExtractor &fe, ObjectClassifier &oc){

	lanesInfo = lanesConfigInfo;
	featureExtractor = fe;
	objectClassifier = oc;
	trckingId = 0;
}

void ObjectTracker::trackingProcess(Mat fRois, vector<vector<Point>> roisContours, Mat currFrame) {
	frame = currFrame;
	nRois = roisContours.size();
	labeledRoisMask = fRois;
	getCurrentFrameObjects();
}

void ObjectTracker::getCurrentFrameObjects(){
	
	detectedObjects.clear();	
	int label;
	float confidence;

	for (size_t i = 0; i < nRois; i++){
		ForegroundObject currentObj(roisContours[i], trckingId);
		if (checkRoiInsideLane(currentObj, i)){
			featureExtractor.getShapeFeatures(currentObj);
			objectClassifier.classifyObject(currentObj, label, confidence);
			if(confidence >= CONFIDENCE_THR)
				detectedObjects.push_back(currentObj);
		}
	}
	showTrackingBBoxes(detectedObjects);
}

bool ObjectTracker::checkRoiInsideLane(ForegroundObject tObj, size_t roiIdx){
	
	bool roiInLane = false;
	Scalar v;
	Scalar interceptionSum;
	Mat singleRoiMask;
	Mat maskLaneInterception;
	
	v.val[0] = roiIdx;
	compare(labeledRoisMask, v, singleRoiMask, cv::CMP_EQ);
    singleRoiMask = singleRoiMask / 255;

	for each(Lane laneInfo in lanesInfo){
		cv::multiply(singleRoiMask, laneInfo.mask, maskLaneInterception);
		interceptionSum = cv::sum(maskLaneInterception);
		if (interceptionSum.val[0] > 0)
			roiInLane = true;
	}	
	return roiInLane;
}

bool ObjectTracker::checkRoiIsVehicle(ForegroundObject tObj) {

	return true;
}

void ObjectTracker::getNearestRois(){

	cv::Point tOCentroid, dOCentroid;
	std::vector<double> distances;
	double d;
	nearestRoisRank.clear();

	for each(ForegroundObject trackedObj in trackedObjects){
		tOCentroid = trackedObj.centroid;
		distances.clear();

		for each(ForegroundObject detectedObj in detectedObjects){
			dOCentroid = detectedObj.centroid;
			d = cv::norm(tOCentroid - dOCentroid);
			distances.push_back(d);
		}
		nearestRoisRank.push_back(sortVectorGetIndexes(distances));
	}
}

void ObjectTracker::showTrackingBBoxes(vector<ForegroundObject> objects){

	int nRois = objects.size();
	
	cv::Point dl, ur;

	for each(ForegroundObject object in objects){
		dl = object.botLeftCoord;
		ur = cv::Point(dl.x + object.width, dl.y + object.height);
		rectangle(frame, dl, ur, object.color, 2);
	}
	cv::imshow("People Det", frame);
	cv::waitKey();
}

vector<size_t> ObjectTracker::sortVectorGetIndexes(vector<double> vecA){

	// initialize original index locations
	vector<size_t> indexes(vecA.size());
	std::iota(indexes.begin(), indexes.end(), 0);

	// sort indexes based on comparing values in v
	sort(indexes.begin(), indexes.end(),
		[&vecA](size_t i1, size_t i2) {return vecA[i1] < vecA[i2]; });

	return indexes;
}
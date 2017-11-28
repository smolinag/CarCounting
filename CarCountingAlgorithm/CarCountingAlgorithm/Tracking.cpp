#include "Tracking.h"

Tracking::Tracking(){

}

Tracking::Tracking(vector<Lane> lanesConfigInfo){

	lanesInfo = lanesConfigInfo;
	trckingId = 0;
}

void Tracking::getCurrentFrameObjects(int numRois, Mat fRois, vector<vector<Point>> roisContours, Mat currFrame){

	frame = currFrame;
	detectedObjects.clear();
	nRois = numRois;
	labeledRoisMask = fRois;

	for (size_t i = 0; i < nRois; i++){
		TrackedObject tObj(roisContours[i], trckingId);

		if (checkRoiInsideLane(tObj, i)){
			detectedObjects.push_back(tObj);
		}
	}
	showTrackingBBoxes(detectedObjects);
}

bool Tracking::checkRoiInsideLane(TrackedObject tObj, size_t roiIdx){
	
	bool roiInLane = false;
	Scalar v;
	Scalar interceptionSum;
	Mat singleRoiMask;
	Mat maskLaneInterception;
	
	v.val[0] = roiIdx;
	compare(labeledRoisMask, v, singleRoiMask, cv::CMP_EQ);
    singleRoiMask = singleRoiMask / 255;

	for (size_t j = 0; j < lanesInfo.size(); j++){

		cv::multiply(singleRoiMask, lanesInfo[j].mask, maskLaneInterception);
		interceptionSum = cv::sum(maskLaneInterception);

		if (interceptionSum.val[0] > 0)
			roiInLane = true;
	}
	
	return roiInLane;
}

void Tracking::getNearestRois(){

	cv::Point tOCentroid, dOCentroid;
	std::vector<double> distances;
	double d;
	nearestRoisRank.clear();

	for (size_t i = 0; i < trackedObjects.size(); i++){
		tOCentroid = trackedObjects[i].centroid;
		distances.clear();

		for (size_t j = 0; j < detectedObjects.size(); j++){
			dOCentroid = detectedObjects[j].centroid;
			d = cv::norm(tOCentroid - dOCentroid);
			distances.push_back(d);
		}
		nearestRoisRank.push_back(sortVectorGetIndexes(distances));
	}
}

void Tracking::showTrackingBBoxes(vector<TrackedObject> objects){

	int nRois = objects.size();
	
	cv::Point dl, ur;

	for (size_t i = 0; i < nRois; i++){
		dl = objects[i].botLeftCoord;
		ur = cv::Point(dl.x + objects[i].width, dl.y + objects[i].height);
		rectangle(frame, dl, ur, objects[i].color, 2);
	}
	cv::imshow("People Det", frame);
	cv::waitKey();
}

vector<size_t> Tracking::sortVectorGetIndexes(vector<double> vecA){

	// initialize original index locations
	vector<size_t> indexes(vecA.size());
	std::iota(indexes.begin(), indexes.end(), 0);

	// sort indexes based on comparing values in v
	sort(indexes.begin(), indexes.end(),
		[&vecA](size_t i1, size_t i2) {return vecA[i1] < vecA[i2]; });

	return indexes;
}
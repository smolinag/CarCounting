#include "Tracking.h"

Tracking::Tracking(){

}

Tracking::Tracking(vector<Lane> lanesConfigInfo){

	lanesInfo = lanesConfigInfo;
	trckingId = 0;
}

void Tracking::getCurrentFrameObjects(int nRois, cv::Mat fRois, std::vector<std::vector<cv::Point>> roisContours, cv::Mat currFrame){

	frame = currFrame;
	detectedObjects.clear();

	for (size_t i = 0; i < nRois; i++){
		TrackedObject tObj(roisContours[i], trckingId);

		detectedObjects.push_back(tObj);
	}
	showTrackingBBoxes(detectedObjects);
}

bool Tracking::checkRoiInsideLane(TrackedObject tObj){
	//TO DO

	return true;
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

void Tracking::showTrackingBBoxes(std::vector<TrackedObject> objects){

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

std::vector<std::size_t> Tracking::sortVectorGetIndexes(std::vector<double> vecA){

	// initialize original index locations
	std::vector<std::size_t> indexes(vecA.size());
	std::iota(indexes.begin(), indexes.end(), 0);

	// sort indexes based on comparing values in v
	sort(indexes.begin(), indexes.end(),
		[&vecA](std::size_t i1, std::size_t i2) {return vecA[i1] < vecA[i2]; });

	return indexes;
}
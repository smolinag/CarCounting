#include "Tracking.h"

Tracking::Tracking(){

	trckingId = 0;
}

void Tracking::getCurrentFrameObjects(int nRois, cv::Mat fRois, std::vector<std::vector<cv::Point>> roisContours, cv::Mat currFrame){

	frame = currFrame;
	detectedObjects.clear();

	for (size_t i = 0; i < nRois; i++){
		detectedObjects.push_back(TrackedObject(roisContours[i], trckingId));
	}
	showTrackingBBoxes(detectedObjects);
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
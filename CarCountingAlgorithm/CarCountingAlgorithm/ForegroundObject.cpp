#include "ForegroundObject.h"

ForegroundObject::ForegroundObject(std::vector<cv::Point> roiContour, int roiId){

	id = roiId;
	color = cv::Scalar(ColorLib[id][0], ColorLib[id][1], ColorLib[id][2]);
	contour = roiContour;
	getStatesFromContour(roiContour);
}

void ForegroundObject::getStatesFromContour(std::vector<cv::Point> roiContour){

	int minX = 9999;
	int maxX = 0;
	int minY = 9999;
	int maxY = 0;
	int pX, pY;

	//Get minimum and maximun of ROIs bounding boxes
	for (size_t i = 0; i < roiContour.size(); i++){		
		pX = roiContour[i].x;
		pY = roiContour[i].y;

		if (pX > maxX){
			maxX = pX;
		}
		if (pX < minX){
			minX = pX;
		}			
		if (pY > maxY){
			maxY = pY;
		}
		if (pY < minY){
			minY = pY;
		}
	}

	//Get states
	botLeftCoord.x = minX;
	botLeftCoord.y = minY;
	width = maxX - minX;
	height = maxY - minY;
	centroid.x = minX + int(floor(double(width) / 2.));
	centroid.y = minY + int(floor(double(height) / 2.));
}
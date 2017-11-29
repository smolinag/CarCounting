#include "ForegroundPostProcessing.h"

ForegroundPostProcessing::ForegroundPostProcessing(){
	//Initialize variables	
	morphSize1 = 5;
	morphElement1 = cv::getStructuringElement(2, cv::Size(2 * morphSize1 + 1, 2 * morphSize1 + 1), cv::Point(morphSize1, morphSize1));
	morphSize2 = 5;
	morphElement1 = cv::getStructuringElement(2, cv::Size(2 * morphSize2 + 1, 2 * morphSize2 + 1), cv::Point(morphSize2, morphSize2));
}

void ForegroundPostProcessing::postProcessingMain(const cv::Mat &fMask){
	
	//Perform foreground mask closing
	morphologyEx(fMask, fMask, 3, ForegroundPostProcessing::morphElement1);	

	//Delete small regions
	deleteSmallRegions(fMask);

	//Find final countours
	cv::Mat A = fMask.clone();
	cv::findContours(A, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

	//Fill holes
	fillHoles(fMask);
	fMaskPost = fMask;
}

//Deletes regions smaller than a percentage of the frame size according to the size of their countours
void ForegroundPostProcessing::deleteSmallRegions(const cv::Mat &fMask){

	int frameHeight = fMask.rows;
	int frameWidth = fMask.cols;
	float pminArea = 0.001;
	minArea = int(pminArea*float(frameHeight*frameWidth));  //Minimum area to consider a region

	//Find initial countours
	cv::Mat A = fMask.clone();
	cv::findContours(A, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//Loop through countours finding regions with short contours (therefore small area)
	for (size_t i = 0; i < contours.size(); i++)
	{
		if (contours[i].size() < minArea)
		{
			//delete small regions
			pt.x = contours[i][0].x;
			pt.y = contours[i][0].y;
			floodFill(fMask, pt, cv::Scalar::all(0), 0, cv::Scalar(), cv::Scalar(), 8);
		}
	}
}

//Fills the holes inside foreground regions
void ForegroundPostProcessing::fillHoles(const cv::Mat &fMask){

	//Loop through countours finding inner contours to fill them
	for (size_t i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][3] != -1)
		{
			pt.x = contours[i][0].x + 1;
			pt.y = contours[i][0].y + 1;
			floodFill(fMask, pt, cv::Scalar::all(255));
		}
	}
}

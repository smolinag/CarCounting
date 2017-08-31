#include "ForegroundPostProcessing.h"


ForegroundPostProcessing::ForegroundPostProcessing(const cv::Mat iniFrame){

	//Initialize variables
	int frameHeight = iniFrame.rows;
	int frameWidth = iniFrame.cols;
	float pminArea = 0.001;
	minArea = int(pminArea*float(frameHeight*frameWidth));  //Minimum area to consider a region
	morphSize1 = 5;
	morphElement1 = cv::getStructuringElement(2, cv::Size(2 * morphSize1 + 1, 2 * morphSize1 + 1), cv::Point(morphSize1, morphSize1));
	morphSize2 = 5;
	morphElement1 = cv::getStructuringElement(2, cv::Size(2 * morphSize2 + 1, 2 * morphSize2 + 1), cv::Point(morphSize2, morphSize2));
}

void ForegroundPostProcessing::postProcessingMain(const cv::Mat &fMask){

	//Perform foreground mask closing
	morphologyEx(fMask, fMask, 3, ForegroundPostProcessing::morphElement1);
	cv::imshow("fMask", fMask);

	//Delete small regions
	deleteSmallRegions(fMask);

	//Find final countours
	cv::Mat A = fMask.clone();
	cv::findContours(A, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

	//Fill holes
	fillHoles(fMask);

	//Label isolated regions and store their contours
	cv::Mat fRoi;
	int nFRois = roiLabelling(fMask, fRoi);

	//Displays labeled regions
	imagesc(fRoi, nFRois, "Foreground ROIs");
}

//Deletes regions smaller than a percentage of the frame size according to the size of their countours
void ForegroundPostProcessing::deleteSmallRegions(const cv::Mat &fMask){

	//Find initial countours
	cv::Mat A = fMask.clone();
	cv::findContours(A, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//Loop through countours finding regions with short contours (therefore small area)
	for (int i = 0; i < contours.size(); i++)
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
	for (int i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][3] != -1)
		{
			pt.x = contours[i][0].x + 1;
			pt.y = contours[i][0].y + 1;
			floodFill(fMask, pt, cv::Scalar::all(255));
		}
	}
}

//Given a foregrounf image (binary), labels each isolated region. 
//It also stores the coordinates of their countours
int ForegroundPostProcessing::roiLabelling(cv::Mat fMask, cv::Mat &bwFMask){
	
	bwFMask = fMask.clone();
	int Nroi = 0;

	//Variables to store contours coordinates of each isolated region 
	xCoordRoiCountour.clear();
	yCoordRoiCountour.clear();
	std::vector<int> X_temp;
	std::vector<int> Y_temp;

	for (int i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][3] == -1){

			Nroi++;
			pt.x = contours[i][0].x;
			pt.y = contours[i][0].y;
			floodFill(bwFMask, pt, cv::Scalar::all(Nroi), 0, cv::Scalar(), cv::Scalar(), 8);

			X_temp.clear();
			Y_temp.clear();

			//store contours coordinates
			for (int j = 0; j < contours[i].size(); j++){
				X_temp.push_back(contours[i][j].x);
				Y_temp.push_back(contours[i][j].y);
			}
			xCoordRoiCountour.push_back(X_temp);
			yCoordRoiCountour.push_back(Y_temp);
		}
	}
	return Nroi;
}

//Given a Mat with labeled regions from 1 to N, assigns a different color to each of them and plots it
void ForegroundPostProcessing::imagesc(cv::Mat src, int siz, char* Plotname){
	
	//Color Directory
	cv::Mat output(src.rows, src.cols, CV_8UC3, CV_RGB(0, 0, 0));
	cv::Mat aux = src.clone();
	cv::Mat aux3;
	cv::Scalar v;
	for (int i = 0; i <= siz; i++)
	{
		v.val[0] = i;
		compare(src, v, aux, cv::CMP_EQ);

		aux = aux / 255;

		cv::Mat aux2[] = { aux*Color[i][0], aux*Color[i][1], aux*Color[i][2] };
		merge(aux2, 3, aux3);
		output = aux3 + output;
	}
	imshow(Plotname, output);
}
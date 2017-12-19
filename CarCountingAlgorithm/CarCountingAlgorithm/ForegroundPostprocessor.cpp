#include "ForegroundPostprocessor.h"

ForegroundPostprocessor::ForegroundPostprocessor(){

}

ForegroundPostprocessor::ForegroundPostprocessor(const cv::Mat iniFrame){

	//Initialize variables
	int frameHeight = iniFrame.rows;
	int frameWidth = iniFrame.cols;
	minArea = int(REL_MIN_REGION_AREA*float(frameHeight*frameWidth));  //Minimum area to consider a region
	morphElement = cv::getStructuringElement(2, cv::Size(2 * MORPH_ELEM_SIZE + 1, 2 * MORPH_ELEM_SIZE + 1), cv::Point(MORPH_ELEM_SIZE, MORPH_ELEM_SIZE));
}

void ForegroundPostprocessor::postProcessingMain(const cv::Mat &fMask){
	
	//Perform foreground mask closing
	morphologyEx(fMask, fMask, 3, ForegroundPostprocessor::morphElement);	

	//Delete small regions
	deleteSmallRegions(fMask);

	//Find final countours
	cv::Mat A = fMask.clone();
	cv::findContours(A, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

	//Fill holes
	fillHoles(fMask);
	fMaskPost = fMask;

	//Label isolated regions and store their contours
	nRois = roiLabelling(fMask, labeledRoisMask);

	//Displays labeled regions
	imagesc(labeledRoisMask, nRois, "Foreground ROIs");
}

//Deletes regions smaller than a percentage of the frame size according to the size of their countours
void ForegroundPostprocessor::deleteSmallRegions(const cv::Mat &fMask){

	//Find initial countours
	cv::Mat A = fMask.clone();
	cv::findContours(A, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	cv::Point pt;

	//Loop through countours finding regions with short contours (therefore small area)
	for each(vector<Point> contour in contours) 
	{
		if (contour.size() < minArea)
		{
			//delete small regions
			pt.x = contour[0].x;
			pt.y = contour[0].y;
			floodFill(fMask, pt, cv::Scalar::all(0), 0, cv::Scalar(), cv::Scalar(), 8);
		}
	}
}

//Fills the holes inside foreground regions
void ForegroundPostprocessor::fillHoles(const cv::Mat &fMask){
	cv::Point pt;

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

//Given a foregrounf image (binary), labels each isolated region. 
//It also stores the coordinates of their countours
int ForegroundPostprocessor::roiLabelling(cv::Mat fMask, cv::Mat &roiLabelMask){
	
	roiLabelMask = fMask.clone();
	int Nroi = 0;
	cv::Point pt;

	//Variables to store contours coordinates of each isolated region 
	roisCountours.clear();

	for (size_t i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][3] == -1){

			Nroi++;
			pt.x = contours[i][0].x;
			pt.y = contours[i][0].y;
			floodFill(roiLabelMask, pt, cv::Scalar::all(Nroi), 0, cv::Scalar(), cv::Scalar(), 8);
			roisCountours.push_back(contours[i]);
		}
	}
	return Nroi;
}

//Given a Mat with labeled regions from 1 to N, assigns a different color to each of them and plots it
void ForegroundPostprocessor::imagesc(cv::Mat src, int siz, char* Plotname){
	
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

		cv::Mat aux2[] = { aux*ColorLib[i][0], aux*ColorLib[i][1], aux*ColorLib[i][2] };
		merge(aux2, 3, aux3);
		output = aux3 + output;
	}
	imshow(Plotname, output);
}
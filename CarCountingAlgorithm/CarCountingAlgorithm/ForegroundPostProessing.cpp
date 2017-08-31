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

	//Find countours, store isolated regions contours, delete small isolated regions and plot
	cv::Mat test;
	bwLabel(fMask, test);
}

int ForegroundPostProcessing::bwLabel(cv::Mat fMask, cv::Mat &bwFMask){
	
	cv::Mat cFmask = fMask.clone();

	//morphologyEx(cFmask, cFmask, 3, ForegroundPostProcessing::morphElement2);
	//cv::erode(cFmask, cFmask, ForegroundPostProcessing::morphElement);

	cv::Mat A = cFmask.clone();

	cv::findContours(A, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	int Nroi = 0;

	//Variables to store contours coordinates of each isolated region 
	xCoordRoiCountour.clear();
	yCoordRoiCountour.clear();
	std::vector<int> X_temp;
	std::vector<int> Y_temp;

	for (int i = 0; i<contours.size(); i++)
	{
		if (contours[i].size() >= minArea)
		{
			Nroi++;
			pt.x = contours[i][0].x;
			pt.y = contours[i][0].y;
			floodFill(cFmask, pt, cv::Scalar::all(Nroi));

			X_temp.clear();
			Y_temp.clear();

			//store contours coordinates
			for (int j = 0; j<contours[i].size(); j++){
				X_temp.push_back(contours[i][j].x);
				Y_temp.push_back(contours[i][j].y);
			}
			xCoordRoiCountour.push_back(X_temp);
			yCoordRoiCountour.push_back(Y_temp);
		}
		else
		{
			//delete small regions
			for (int j = 0; j < contours[i].size(); j++){
				pt.x = contours[i][j].x;
				pt.y = contours[i][j].y;
				floodFill(cFmask, pt, cv::Scalar::all(0));
			}			
		}
		/*std::cout << "Size:" << contours[i].size() << "/" << minArea << " px:" << pt.x << " py:" << pt.y << std::endl;
		imagesc(cFmask, Nroi, "test2");
		cv::waitKey();*/
	}
	
	imagesc(cFmask,Nroi,"test2");
	//cv::waitKey();

	return Nroi;
}

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
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/opencv.hpp>
#include "dirent.h"
#include <string.h>
#include "ForegroundPostProcessing.h"
#include "FeatureExtractor.h"

using namespace std;
using namespace cv;

void main() {

	struct dirent *ent;		//Structure to read directories	
	DIR *dir;				//Directory variable
	string main_path_str = "C://Users//jaime.echeverry//Documents//Tests//CarDetection//SideViews//Cars";
	char main_path_ch[250];
	Mat img;
	string imgName;
	Mat imgAlpha;
	Mat imgSplit[4];
	vector<vector<Point>> contours;
	vector<cv::Vec4i> hierarchy;
	vector<Point> keyPoints;
	ForegroundPostProcessing fpp;
	FeatureExtractor fe;

	strcpy_s(main_path_ch, main_path_str.c_str());
	if ((dir = opendir(main_path_ch)) != NULL)
	{
		//Loop through folder items
		while ((ent = readdir(dir)) != NULL)
		{
			//Avoid "." and ".." files
			if (ent->d_namlen > 2)
			{
				imgName = ent->d_name;
				img = imread(main_path_str + "//" + imgName, IMREAD_UNCHANGED);
				split(img, imgSplit);
				threshold(imgSplit[3], imgAlpha, 200, 255, 0);
				fpp.postProcessingMain(imgAlpha);
						
				findContours(imgAlpha, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
				drawContours(imgAlpha, contours, 0, Scalar(255,20,100), 2, 8, hierarchy, 0, Point());

				fe.getShapeFeatures(contours[0], keyPoints, img);
				fe.drawKeyPoints(img, keyPoints);

				imshow("Im: " + imgName, img);
				waitKey();
				destroyWindow("Im: " + imgName);
			}
		}
	}
}
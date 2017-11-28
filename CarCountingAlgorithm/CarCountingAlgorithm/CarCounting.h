#ifndef CarCounting_H
#define CarCounting_H

#include <iostream>;
#include <string>;
#include <fstream>
#include "rapidxml.hpp"
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "ColorLibrary.h"
#include "Datasets_Menu.h"
#include "package_bgs\DPZivkovicAGMM.h"
#include "ForegroundPostProcessing.h"
#include "Tracking.h"
#include "CarCounting.h"

using namespace rapidxml;
using cv::Point;
using cv::Mat;
using std::string;
using std::vector;
using cv::Scalar;

class CarCounting{

public:

	CarCounting();

	~CarCounting();
	
	int executeAlgorithm();

	int reportDetection();

	string camName;
	string camLocation;
	int frameWidth;
	int frameHeight;

private:

	int loadXMLConfiguration(string XMLFilePath);

	int drawLanesMask();

	IBGS *bgs;		//Bacground subtracion object
	Datasets_Menu datasetsMenuObj;	//Datasets selection object
	ForegroundPostProcessing fgroundPPObj; //Foreground post processing object
	Tracking trackingObj; //Tracking object

	vector<Lane> lanesInfo;		//Lanes configuration information

	Mat frameLanesConfig;//Lanes configuration drawn on the frame 
	Mat oFrame;			//Original frame (higher resolution)
	Mat frame;			//Processed frame (resized)
	Mat fground;		//Foreground mask
	Mat bgroundModel;	//Background model
	Mat labeledRoisMask;//Labeled foreground ROIs

	//Time vars
	double t1, t2;	
};
#endif;
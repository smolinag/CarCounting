#ifndef CarCounting_H
#define CarCounting_H

#include <iostream>;
#include <string>;
#include <fstream>
#include "rapidxml.hpp"
#include <vector>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "ColorLibrary.h"

using namespace rapidxml;
using cv::Point;
using cv::Mat;
using std::string;
using std::vector;

struct Lane{
	int id;
	int direction;
	vector<Point> polygonPoints;
};

class CarCounting{

public:

	CarCounting();

	~CarCounting();

	int loadXMLConfiguration(string XMLFilePath);

	int executeAlgorithm();

	int reportDetection();

	string camName;
	string camLocation;
	int frameWidth;
	int frameHeight;

private:

	int generateLanesMask();

	vector<Lane> lanes;
};
#endif;
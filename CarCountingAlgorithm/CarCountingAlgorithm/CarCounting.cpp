#include "CarCounting.h"

CarCounting::CarCounting(){

	//Load XML Configuration
	loadXMLConfiguration("./config/HomeCam5.xml");

	//Initialize datast object and select record source
	datasetsMenuObj = Datasets_Menu();
	datasetsMenuObj.Select_Dataset();

	//Load initial frame	
	datasetsMenuObj.Get_Frame(oFrame);
	resize(oFrame, frame, cv::Size(480, 320));

	//Initialize background subtraction  object	
	bgs = new DPZivkovicAGMM;

	//Initialize foreground Postprocessing object
	fgroundPPObj = ForegroundPostProcessing(frame);

	//Initialize tracking object
	trackingObj = Tracking();
}

CarCounting::~CarCounting(){

	delete bgs;
}

int CarCounting::executeAlgorithm(){

	//Get new frame
	datasetsMenuObj.Get_Frame(oFrame);

	//If frame is empty return -1
	if (oFrame.empty())
		return -1;

	//Perform background subtraction
	t1 = (double)cvGetTickCount();
	resize(oFrame, frame, cv::Size(480, 320));
	bgs->process(frame, fground, bgroundModel);
	t2 = (double)cvGetTickCount();
	printf("\nBGS time: %gms", (t2 - t1) / (cvGetTickFrequency()*1000.));
	//imshow("Gaussian Mixture Model (Zivkovic)", fground);

	//Perform foreground postprocess
	t1 = (double)cvGetTickCount();
	fgroundPPObj.postProcessingMain(fground);
	t2 = (double)cvGetTickCount();
	printf("\nPostprocess time: %gms", (t2 - t1) / (cvGetTickFrequency()*1000.));

	//Get objects from foreground regions
	trackingObj.getCurrentFrameObjects(fgroundPPObj.nRois, fgroundPPObj.fMaskPost, fgroundPPObj.roisCountours, frame);

	//imshow("Frame", Fr);
	//waitKey();

	return 0;
}

int CarCounting::loadXMLConfiguration(std::string XMLFilePath){

	xml_attribute<> *pAttr;

	// Read the xml file into a vector
	std::ifstream theFile(XMLFilePath);
	vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	if (buffer.empty())
		return -1;
	buffer.push_back('\0');

	// Parse the buffer using the xml file parsing library into doc 
	xml_document<> doc;
	doc.parse<0>(&buffer[0]);

	// Find CamConfig node
	xml_node<> * root_node;
	root_node = doc.first_node("CamConfig");

	// Find Cam node and get its attributes
	xml_node<> * cam_node;
	cam_node = root_node->first_node("Cam");

	//Get name
	pAttr = cam_node->first_attribute("name");
	camName = pAttr->value();

	//Get location
	pAttr = cam_node->first_attribute("location");
	camLocation = pAttr->value();

	//Get resolution
	pAttr = cam_node->first_attribute("resolution");
	string res = pAttr->value();
	size_t pos = res.find("x");
	frameWidth = atoi(res.substr(0, pos).c_str());
	frameHeight = atoi(res.substr(pos+1, res.size()).c_str());

	//Iterate through lanes
	xml_node<> * lane_node;
	Lane lane;
	vector<Point> polyPoints;
	for (lane_node = cam_node->first_node("Lane"); lane_node; lane_node = lane_node->next_sibling()){

		//Get Id
		pAttr = lane_node->first_attribute("id");
		lane.id = atoi(pAttr->value());

		//Get Direction
		pAttr = lane_node->first_attribute("direction");
		lane.direction = atoi(pAttr->value());

		//Get polygon points
		xml_node<> * polyPoint_node;
		polyPoints.clear();
		Point p;
		for (polyPoint_node = lane_node->first_node("PolyPoint"); polyPoint_node; polyPoint_node = polyPoint_node->next_sibling()){

			//Get point
			pAttr = polyPoint_node->first_attribute("x");
			p.x = atoi(pAttr->value());
			pAttr = polyPoint_node->first_attribute("y");
			p.y = atoi(pAttr->value());
			polyPoints.push_back(p);
		}
		lane.polygonPoints = polyPoints;
	}
	//Store lanes
	lanes.push_back(lane);

	generateLanesMask();

	return 0;
}

int CarCounting::generateLanesMask(){

	Mat test = Mat(frameHeight, frameWidth, CV_8UC3, cv::Scalar(0,0,0));

	for (size_t i = 0; i < lanes.size(); i++){

		vector<Point> tmp = lanes[0].polygonPoints;
		const Point* elementPoints[1] = { &tmp[0] };
		int numPoints[] = { tmp.size() };
		cv::fillPoly(test, elementPoints, numPoints, 1, cv::Scalar(Color[i][0], Color[i][1], Color[i][2]), 8);
	}
	
	imshow("test", test);
	cv::waitKey();

	return 0;
}


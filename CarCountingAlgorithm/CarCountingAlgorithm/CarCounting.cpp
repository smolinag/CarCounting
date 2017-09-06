#include "CarCounting.h"

CarCounting::CarCounting(){

	loadXMLConfiguration("./config/HomeCam5.xml");
}

CarCounting::~CarCounting(){

	
}

int CarCounting::loadXMLConfiguration(std::string XMLFilePath){

	xml_attribute<> *pAttr;

	// Read the xml file into a vector
	std::ifstream theFile(XMLFilePath);
	vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
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

	return 0;
}


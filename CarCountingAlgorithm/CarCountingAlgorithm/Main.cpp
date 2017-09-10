#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "CarCounting.h"


void main(){

	//Create main object 
	CarCounting CC;
	int execFlag = 0;

	//Execute algorithm as long as there are frames
	while (execFlag == 0){		
		execFlag = CC.executeAlgorithm();
	}
}
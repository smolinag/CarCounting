#include "Datasets_Menu.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

void main(){
	Datasets_Menu DM;
	
	DM.Select_Dataset();

	//Load initial frame
	Mat Fr_o, Fr;
	DM.Get_Frame(Fr_o);
	resize(Fr_o, Fr, Size(640, 480));

	for (;;){
		DM.Get_Frame(Fr_o);
		resize(Fr_o, Fr, Size(640, 480));

		if (Fr.empty())
			break;

		imshow("Frame", Fr);
		waitKey(1);
	}
}
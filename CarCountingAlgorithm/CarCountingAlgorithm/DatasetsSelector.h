#ifndef DatasetsSelector_H
#define DatasetsSelector_H

#include <iostream>
#include "dirent.h"
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <fstream>


using namespace std;

class DatasetsSelector
{
public:

	//--------------------------------Main functions---------------------------------
	DatasetsSelector();

	~DatasetsSelector();

	void Select_Dataset();

	void Get_Frame(cv::Mat &Fr);	

private:
	//-----------------------------Auxiliar functions---------------------------------
	void Loop_Options(DIR *dir, string &main_path, int &fmt);

	int Check_Extension(string file);

	void Display_Menu(vector<string> menu);

	void Set_shortcut_DB(int fmt, string path);

	void Get_shortcut_DB(int &fmt, string &path);

	//-----------------------------------Variables------------------------------------
	cv::VideoCapture Source;	//Videocapture for video files
		
	struct dirent *ent;			//Structure to read directories	
	DIR *dir_seq;				//Directory variable

	string main_path_str;		//Main string for path directory
	char main_path_ch[250];		//Main char array for path directory

	int fmt;					//Category id (1:image, 2:video, 3:folder, 4:other)
	
	int lvl;					//Searching level in directory
	
	bool valid;					//If the selected directory has a sequence or video: true

	vector<string> img_fmt;		//Valid image formats
	vector<string> vid_fmt;		//Valid video formats
};
#endif;
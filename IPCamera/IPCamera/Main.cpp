#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

#include <direct.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

using namespace cv;
using namespace std;


//Save frames info
bool saveFramesFlag = true;
string savePath = "D:\\Documentos\\Proyectos\\Analisis de trafico vehicular\\VideosDB\\";
string vidName = "IpCam3";
int frIdx = 1;
int zeroNum = 6;
string ext = ".jpg";

//Functions
void createFolder();
bool dirExists(const char *path);
void storeFrames(Mat A);


//Main
int main(){

	VideoCapture Video;
	Mat Im;
	Video.open("http://192.168.1.150:81/videostream.cgiuser=admin&pwd=molina92&resolution=32&rate=10.mjpg");	

	//Create folder to store frames
	if (saveFramesFlag){
		createFolder();
	}

	if (!Video.isOpened())
		printf("camera is null\n");
	else
	{
		printf("camera is not null");
		cvNamedWindow("img");

		while (waitKey(10) != atoi("q"))
		{
			double t1 = (double)cvGetTickCount();
			Video >> Im;
			imshow("Frame", Im);
			
			//Save current frame
			if (saveFramesFlag){
				storeFrames(Im);
				frIdx++;
			}

			double t2 = (double)cvGetTickCount();
			printf("time: %gms  fps: %.2g\n", (t2 - t1) / (cvGetTickFrequency()*1000.), 1000. / ((t2 - t1) / (cvGetTickFrequency()*1000.)));
		}
		Video.release();
	}
}

//Creates directory or overwrites files according to user input
void createFolder(){
	
	String path = savePath + vidName;
	char pathCh[1024];
	strncpy(pathCh, path.c_str(), sizeof(pathCh));
	pathCh[sizeof(pathCh) - 1] = 0;

	cout << pathCh << endl;

	if (dirExists(pathCh)){
		cout << "Directory already exists. Overwrite files? (y/n)" << endl;
		string overwriteFlag;
		cin >> overwriteFlag;

		if (overwriteFlag == "n")
			saveFramesFlag = false;
	}
	else{
		cout << "Directory does not exist. Would you like to create it? (y/n)" << endl;
		string createFlag;
		cin >> createFlag;

		if (createFlag == "y")
			_mkdir(pathCh);
	}
}

//Checks if a given directory exists
bool dirExists(const char *path)
{
	struct stat info;

	if (stat(path, &info) != 0)
		return false;
	else if (info.st_mode & S_IFDIR)
		return true;
	else
		return false;
}

//Stores the frames of an input videostrem in a given path
void storeFrames(Mat A){

	string frIdxStr = std::to_string(frIdx);
	string frIdxStrPad = std::string(zeroNum - frIdxStr.length(), '0') + frIdxStr;
	string path = savePath + vidName + "\\" + frIdxStrPad + ext;

	imwrite(path, A);
}



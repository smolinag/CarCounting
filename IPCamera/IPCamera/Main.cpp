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
string vidName;
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

	//Set IpCam to preset position 1, see CGI commands for more info
	Video.open("http://192.168.1.150:81/decoder_control.cgicommand=31user=admin&pwd=molina92");
	Video.release();
	system("cls");

	Video.open("http://192.168.1.150:81/videostream.cgiuser=admin&pwd=molina92&resolution=32&rate=10.mjpg");	

	//Create folder to store frames
	if (saveFramesFlag){
		createFolder();
	}

	if (!Video.isOpened())
		cout << "Camera is null" << endl;
	else
	{

		while (1)
		{
			double t1 = (double)cvGetTickCount();
			Video >> Im;
			//imshow("Frame", Im);
			
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
	
	cout << "Enter a name for the video to record: ";
	cin >> vidName;
	String path = savePath + vidName;
	char pathCh[1024];
	strncpy(pathCh, path.c_str(), sizeof(pathCh));
	pathCh[sizeof(pathCh) - 1] = 0;


	if (dirExists(pathCh)){
		cout << endl << "Directory: \"" << pathCh << "\"already exists." << endl << "Overwrite files ? (y / n)";
		string overwriteFlag;
		cin >> overwriteFlag;

		if (overwriteFlag == "n")
			saveFramesFlag = false;
	}
	else{
		cout << endl << "Directory: \"" << pathCh << "\" does not exist." << endl << "Would you like to create it? (y / n)" << endl;
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



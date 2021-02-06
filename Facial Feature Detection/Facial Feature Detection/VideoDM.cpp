// VideoDM.cpp handles the methods for Video Datamodel
// Author Craig Hunter

//Constructor
#include "videoDM.h"
#include "fileInput.h"
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

//Constructor
VideoDM::VideoDM(string txtFileLocation) {
	image = new BMPFrame[11];
	int start;
	int end;
	LoadDataModel(txtFileLocation);
	location = txtFileLocation;
}


//Deconstructor
VideoDM::~VideoDM() {

}


bool VideoDM::LoadDataModel(string location) {
	char BMP[1024];
	string output;
	int counter = 0;
	for (int i = start; i <= (NumberofFrames); i++) {
		output = location + "Frame" + to_string(i) + ".bmp";
		strcpy_s(BMP, output.c_str());
		//std::cout << "Datamodel [" << (i-1) << "]: " << BMP << endl;
		image[counter].LoadImage((char*)BMP);
		counter++;
	}
	return true;
}

void VideoDM::IncreaseByOne() {
	char BMP[1024];
	string output;
	start = start + 1;
	end = end + 1;
	int counter2 = 0;
	for (int i = start; i <= (end - 1); i++) {
		output = location + "Frame" + to_string(i) + ".bmp";
		strcpy_s(BMP, output.c_str());

		image[counter2].LoadImage((char*)BMP);
		counter2++;
	}
	return;
}
// DataModel.cpp handles the methods for DataModel obj
// Author Craig Hunter
#include "DataModel.h"
#include "fileInput.h"
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

//Constructor
DataModel::DataModel(string txtFileLocation) {
	image = new BMPFrame[NumberofFrames];
}

DataModel::DataModel() {
}

//Deconstructor
DataModel::~DataModel() {

}

bool DataModel::LoadDataModel(string location) {
	char BMP[1024];
	image = new BMPFrame[NumberofFrames];
	string output;

	for (int i = 0; i <= (NumberofFrames - 1); i++) {
		output = location + "Frame" + to_string(i) + ".bmp";
		strcpy_s(BMP, output.c_str());
		image[i].LoadImage((char*)BMP);
	}
	return true;
}
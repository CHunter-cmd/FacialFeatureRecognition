// FullDataModel.cpp handles the methods for the DataModel Obj
// Author Craig Hunter
#include "DataModel.h"
#include "FullDataModel.h"
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

//Constructor
FullDataModel::FullDataModel(string txtFileLocation) {
	numOfDataModels = readTxtFileNumDataModel(txtFileLocation); // Currently Support 1 DataModel per NM and DB
	Model = new DataModel[numOfDataModels];

	// Loading Each Model with Correct num of Frames to Capture
	for (int i = 0; i < numOfDataModels; i++) {
		Model[i].NumberofFrames = readFrameNum(txtFileLocation, i);
	}

	// Loading Each Model with Correct File Directory;
	for (int i = 0; i < numOfDataModels; i++) {
		Model[i].LoadDataModel(readDirLocation(txtFileLocation, i));
	}
}

//Deconstructor
FullDataModel::~FullDataModel() {

}

int FullDataModel::readFrameNum(string txtFileLocation, int iteration) {
	string line;
	ifstream file(txtFileLocation); // Stores directories file
	getline(file, line);
	getline(file, line);
	for (int i = 0; i <= iteration; i++) {
		getline(file, line);
		getline(file, line);
	}
	return stoi(line);
}

int FullDataModel::readTxtFileNumDataModel(string txtFileLocation) {
	string line;
	ifstream file(txtFileLocation); // Stores directories file
	getline(file, line);
	getline(file, line);
	return stoi(line);
}

string FullDataModel::readDirLocation(string txtFileLocation, int iteration) {
	string line;
	ifstream file2(txtFileLocation); // Stores directories file
	getline(file2, line);

	for (int x = 1; x <= (iteration + 1); x++) {
		getline(file2, line);
		getline(file2, line);
	}
	return line;
}
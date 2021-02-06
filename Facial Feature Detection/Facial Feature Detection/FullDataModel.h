// FullDataModel.h handles the methods for the a total datamodel for comparasions
// Author Craig Hunter
#ifndef FullDataModel_H
#define FullDataModel_H
#include "DataModel.h"

class FullDataModel {

public:
	// constructor
	FullDataModel(string txtFileLocation);

	// destructor
	~FullDataModel();

	// load image
	bool LoadDataModel(string location);
	int readTxtFileNumDataModel(string txtFileLocation);
	string readDirLocation(string txtFileLocation, int iteration);
	int readFrameNum(string txtFileLocation, int iteration);

	string location = "";
	int NumberofFrames;
	int numOfDataModels;
	DataModel* Model;
};
#endif // !FullDataModel_H

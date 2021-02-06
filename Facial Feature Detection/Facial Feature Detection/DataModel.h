// DataModel.h handles the methods for DataModel.cpp
// Author Craig Hunter

#include <string>
#include "greyScaleConversion.h"

#ifndef DataModel_H
#define DataModel_H

class DataModel {

public:
	// constructor
	DataModel(string txtFileLocation);
	DataModel();

	// destructor
	~DataModel();

	// load image
	bool LoadDataModel(string location);

	int readTxtFileNumDataModel(string txtFileLocation);


	string location = "";
	int NumberofFrames;
	int numOfDataModels;
	BMPFrame* image;


};



#endif // !DataModel_H


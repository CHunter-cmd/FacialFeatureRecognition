// videoDM.h handles the methods for videoData.cpps
// Author Craig Hunter
#ifndef VIDEODM_H
#define VIDEODM_H

#include "greyScaleConversion.h"
#include "DataModel.h"
class VideoDM{

public:
	// constructor for video DataModel 
	VideoDM(string txtFileLocation); 

	// destructor for  video DataModel
	~VideoDM();

	// load image
	bool LoadDataModel(string location); // Loading the image with the initial 11 Frames
	void IncreaseByOne(); // Increasing the frames held in the clip


	string location = ""; // Intialising the location string
	int NumberofFrames = 11; // Setting the number of frames held in the object
	int start = 1;
	int end = 11;
	BMPFrame* image;
	//private:

};






#endif // !VIDEODM_H


// GreyScaleConversion.h handles the methods for converting bitmap image to greyscale
// Author Unknown
#ifndef greyScaleConversion_H
#define greyScaleConversion_H

#include <fstream>
#include "BMPHeader.h"
#include <iostream>
using namespace std;

class BMPFrame
{
public:
	// constructor
	BMPFrame();
	BMPFrame(char* name);
	// destructor
	~BMPFrame();

	// load image
	bool LoadImage(char* name);
	// write image
	void WriteImage(char* name);

	// image data
	unsigned int** data;
	int height;
	int width;
	int total_pixels;
	float mean;

	// auxilary data of the image
	float** zdata, ** zdata2;
	float** ddata;

	// norm
	void GetNorm(int min_patchsize, int max_patchsize);
	float*** norm;

private:
	// bitmap header
	TBMPHeader BMPHeader;

	// load bmp header
	void LoadHeader(ifstream& inf);
	// write bmp header
	void WriteHeader(ofstream& of);

	// get global mean
	void GetGlobalMean();
	// remove mean
	 // local_patch_size = 0: no mean removal
	 // local_patch_size < 0: remove global mean
	 // local_patch_size > 0: remove local mean
	void RemoveMean(int local_patch_size = 0);
	// get dynamic feature
	void GetDelta(int D);
};
//---------------------------------------------------------------------------

#endif // !greyScaleConversion_H

// GreyScaleConversion.cpp handles methods for converting bitmap to greyscale
// Author Unknown
//---------------------------------------------------------------------------
#include "greyScaleConversion.h"
#include <fstream>
using namespace std;
//---------------------------------------------------------------------------
// constructor
BMPFrame::BMPFrame()
{
	data = NULL;
	zdata = NULL; zdata2 = NULL;
	ddata = NULL;
	norm = NULL;
	mean = -1.;
}
//---------------------------------------------------------------------------
// constructor
BMPFrame::BMPFrame(char* name)
{
	data = NULL;
	zdata = NULL; zdata2 = NULL;
	ddata = NULL;
	norm = NULL;
	mean = -1.;

	if (!LoadImage(name)) {
		cout << "Can't open " << name << endl;
		exit(1);
	}
}
//---------------------------------------------------------------------------
// deconstructor
BMPFrame::~BMPFrame()
{
	if (data) {
		for (int i = height - 1; i >= 0; i--) delete[] data[i];
		delete[] data;
	}
	if (zdata) {
		for (int i = height - 1; i >= 0; i--) delete[] zdata[i];
		delete[] zdata;
	}
	if (zdata2) {
		for (int i = height - 1; i >= 0; i--) delete[] zdata2[i];
		delete[] zdata2;
	}
	if (ddata) {
		for (int i = height - 1; i >= 0; i--) delete[] ddata[i];
		delete[] ddata;
	}
	if (norm) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) delete[] norm[i][j];
			delete[] norm[i];
		}
		delete[] norm;
	}
}
//---------------------------------------------------------------------------
// load bmp header
void BMPFrame::LoadHeader(ifstream& inf)
{
	inf.read((char*)BMPHeader.type, 2); 			//reads in type
	inf.read((char*)&BMPHeader.file_size, 4); 		//reads in file size
	inf.read((char*)&BMPHeader.reserved, 4); 		//reads in reserved
	inf.read((char*)&BMPHeader.offset, 4); 			//reads in offset
	inf.read((char*)&BMPHeader.info_header_size, 4); 	//reads in information header size
	inf.read((char*)&BMPHeader.width, 4); 			//reads in width
	inf.read((char*)&BMPHeader.height, 4); 			//reads in height
	inf.read((char*)&BMPHeader.planes, 2); 			//reads in planes
	inf.read((char*)&BMPHeader.bits_per_pixel, 2); 	//reads in bits per data
	inf.read((char*)&BMPHeader.compression, 4); 		//reads in compression type
	inf.read((char*)&BMPHeader.data_size, 4); 		//reads in data size
	inf.read((char*)&BMPHeader.h_resolution, 4); 		//reads in height resolution
	inf.read((char*)&BMPHeader.v_resolution, 4); 		//reads in width resolution
	inf.read((char*)&BMPHeader.colors, 4); 			//reads in colours
	inf.read((char*)&BMPHeader.important_colors, 4); 	//reads in important colours

	if (BMPHeader.compression) {
		cout << "BMP image compressed!" << endl;
		exit(0);
	}

	// color table 8-bit image (no color table for > 8-bit per data images)
	if (BMPHeader.bits_per_pixel == 8) {
		for (int i = 0; i < 256; i++) {
			inf.read((char*)&BMPHeader.color_table[i].blue, 1);
			inf.read((char*)&BMPHeader.color_table[i].green, 1);
			inf.read((char*)&BMPHeader.color_table[i].red, 1);
			inf.read((char*)&BMPHeader.color_table[i].reserved, 1);
		}
	}
}
//---------------------------------------------------------------------------
// write bmp header
void BMPFrame::WriteHeader(ofstream& of)
{
	of.write((char*)BMPHeader.type, 2); 			//writes header
	of.write((char*)&BMPHeader.file_size, 4); 		//writes file size
	of.write((char*)&BMPHeader.reserved, 4); 		//writes reserved
	of.write((char*)&BMPHeader.offset, 4); 			//write offset
	of.write((char*)&BMPHeader.info_header_size, 4); 	//write information header size
	of.write((char*)&BMPHeader.width, 4); 			//write the width
	of.write((char*)&BMPHeader.height, 4); 			//write the height
	of.write((char*)&BMPHeader.planes, 2); 			//write the planes
	of.write((char*)&BMPHeader.bits_per_pixel, 2); 	//write the bits per data
	of.write((char*)&BMPHeader.compression, 4); 		//write the compression type
	of.write((char*)&BMPHeader.data_size, 4); 		//write the data size
	of.write((char*)&BMPHeader.h_resolution, 4); 		//write the height resolution
	of.write((char*)&BMPHeader.v_resolution, 4); 		//write the width resolution
	of.write((char*)&BMPHeader.colors, 4); 			//write the colours
	of.write((char*)&BMPHeader.important_colors, 4); 	//write the important colours

		// color table 8-bit image (no color table for > 8-bit per data images)
	if (BMPHeader.bits_per_pixel == 8) {
		for (int i = 0; i < 256; i++) {
			of.write((char*)&BMPHeader.color_table[i].blue, 1);
			of.write((char*)&BMPHeader.color_table[i].green, 1);
			of.write((char*)&BMPHeader.color_table[i].red, 1);
			of.write((char*)&BMPHeader.color_table[i].reserved, 1);
		}
	}
}
//---------------------------------------------------------------------------
// load image
bool BMPFrame::LoadImage(char* name)
{
	// opens image file
	ifstream inf(name, ios::binary);
	if (!inf) {
		cout << "Can't open " << name << endl;
		return false;
	}

	// load header
	LoadHeader(inf);
	// space for image data
	data = new unsigned int* [BMPHeader.height];
	for (int i = 0; i < BMPHeader.height; i++)
		data[i] = new unsigned int[BMPHeader.width];

	// padded zeros at the end of each line unless divides evenly into 4
	int padded_zeros = 4 - (BMPHeader.width % 4);
	if (padded_zeros == 4) padded_zeros = 0;

	// read image data
	for (int i = BMPHeader.height - 1; i >= 0; i--) {
		unsigned char imbyte;
		// read a line of grey scale pixels
		for (int j = 0; j < BMPHeader.width; j++) {
			if (BMPHeader.bits_per_pixel == 8)
				inf.read((char*)&imbyte, 1);	// read only 1 byte for 8-bit data
			else {
				inf.read((char*)&imbyte, 1);	// grey-scale 24-bit data: g=b=r
				inf.read((char*)&imbyte, 1);
				inf.read((char*)&imbyte, 1);
			}
			data[i][j] = imbyte;
		}

		// padded zeros at the end of each line
		for (int j = 0; j < padded_zeros; j++)
			inf.read((char*)&imbyte, 1);
	}
	inf.close();

	// dimension & total number of pixels
	height = BMPHeader.height;
	width = BMPHeader.width;
	total_pixels = BMPHeader.height * BMPHeader.width;

	// global mean
	GetGlobalMean();
	// remove mean
//RemoveMean(Global->LocalMeanPatchSize);
	// get derivatives
//	if(Global->UseDynamicFeature) GetDelta(2);
	return true;
}
//---------------------------------------------------------------------------
// write image
void BMPFrame::WriteImage(char* name)
{
	ofstream of(name, ios::binary);
	// write header
	WriteHeader(of);

	// pad zeros at end of each line though if divides by 4 no padding needed
	int padded_zeros = 4 - (BMPHeader.width % 4);
	if (padded_zeros == 4) padded_zeros = 0;

	// write image data
	for (int i = BMPHeader.height - 1; i >= 0; i--) {
		unsigned char imbyte;
		// write a line of grey-scaled pixels
		for (int j = 0; j < BMPHeader.width; j++) {
			imbyte = data[i][j];
			if (BMPHeader.bits_per_pixel == 8)
				of.write((char*)&imbyte, 1);	// write only 1 byte for 8-bit data
			else {
				of.write((char*)&imbyte, 1);	// grey-scale 24-bit data: g=b=r
				of.write((char*)&imbyte, 1);
				of.write((char*)&imbyte, 1);
			}
		}

		// pad zeros at the end of line
		imbyte = 0;
		for (int j = 0; j < padded_zeros; j++)
			of.write((char*)&imbyte, 1);
	}
	of.close();
}
//---------------------------------------------------------------------------
// get global mean
void BMPFrame::GetGlobalMean()
{
	mean = 0.;
	for (int i = 0; i < BMPHeader.height; i++)
		for (int j = 0; j < BMPHeader.width; j++) mean += (float)data[i][j];
	mean /= (BMPHeader.height * BMPHeader.width);
}
//---------------------------------------------------------------------------
// remove mean
void BMPFrame::RemoveMean(int local_patch_size)
{
	local_patch_size = 0;


	// mean removed data
	zdata = new float* [BMPHeader.height];
	for (int i = 0; i < BMPHeader.height; i++)
		zdata[i] = new float[BMPHeader.width];

	// no mean removal
	if (local_patch_size == 0) {
		for (int i = 0; i < BMPHeader.height; i++)
			for (int j = 0; j < BMPHeader.width; j++)
				zdata[i][j] = (float)data[i][j];
	}

	// remove global mean
	else if (local_patch_size < 0) {
		for (int i = 0; i < BMPHeader.height; i++)
			for (int j = 0; j < BMPHeader.width; j++)
				zdata[i][j] = (float)data[i][j] - mean;
	}

	// remove local mean calculated over a patch of size local_patch_size around each pixel
	else {
		int half_lps = local_patch_size / 2;
		for (int i = 0; i < BMPHeader.height; i++) {
			for (int j = 0; j < BMPHeader.width; j++) {
				// local mean around pixel (i,j)
				int kd = half_lps, ku = half_lps, kl = half_lps, kr = half_lps;
				while (i - kd < 0) { kd--; ku++; }
				while (i + ku >= BMPHeader.height) { ku--; kd++; }
				while (j - kl < 0) { kl--; kr++; }
				while (j + kr >= BMPHeader.width) { kr--; kl++; }

				float pix_mean = 0.; int count = 0;
				for (int u = -kd; u <= ku; u++)
					for (int v = -kl; v <= kr; v++) {
						pix_mean += (float)data[i + u][j + v];
						count++;
					}
				pix_mean /= count;

				// remove local mean
				zdata[i][j] = (float)data[i][j] - pix_mean;
			}
		}
	}

	// squared pixels
	zdata2 = new float* [BMPHeader.height];
	for (int i = 0; i < BMPHeader.height; i++)
		zdata2[i] = new float[BMPHeader.width];

	for (int i = 0; i < BMPHeader.height; i++)
		for (int j = 0; j < BMPHeader.width; j++)
			zdata2[i][j] = zdata[i][j] * zdata[i][j];
}
//---------------------------------------------------------------------------
// get dynamic feature
void BMPFrame::GetDelta(int D)
{
	ddata = new float* [BMPHeader.height];
	for (int i = 0; i < BMPHeader.height; i++)
		ddata[i] = new float[BMPHeader.width];

	int N = 0;
	for (int d = 1; d <= D; d++) N += d * d;
	N *= 2;

	// temp
	float** temp = new float* [BMPHeader.height];
	for (int i = 0; i < BMPHeader.height; i++)
		temp[i] = new float[BMPHeader.width];

	// f'(i,j) = df(i,j)/dj
	for (int i = 0; i < BMPHeader.height; i++)
		for (int j = 0; j < BMPHeader.width; j++) {
			float dfdj = 0.;
			for (int d = 1; d <= D; d++) {
				int j0 = (j - d > 0) ? j - d : 0;
				int j1 = (j + d < BMPHeader.width) ? j + d : BMPHeader.width - 1;
				dfdj += ((float)data[i][j1] - (float)data[i][j0]) * d;
			}
			temp[i][j] = dfdj / N;
		}

	// f''(i,j) = df'(i,j)/di = d^2f(i,j)/didj
	for (int j = 0; j < BMPHeader.width; j++)
		for (int i = 0; i < BMPHeader.height; i++) {
			float dfdi = 0.;
			for (int d = 1; d <= D; d++) {
				int i0 = (i - d > 0) ? i - d : 0;
				int i1 = (i + d < BMPHeader.height) ? i + d : BMPHeader.height - 1;
				dfdi += (temp[i1][j] - temp[i0][j]) * d;
			}
			ddata[i][j] = dfdi / N;
		}

	for (int i = 0; i < BMPHeader.height; i++) delete[] temp[i];
	delete[] temp;

	// squared delta
	for (int i = 0; i < BMPHeader.height; i++)
		for (int j = 0; j < BMPHeader.width; j++)
			zdata2[i][j] += ddata[i][j] * ddata[i][j];
}
//---------------------------------------------------------------------------
void BMPFrame::GetNorm(int min_patchsize, int max_patchsize)
{
	norm = new float** [height];
	for (int i = 0; i < height; i++) {
		norm[i] = new float* [width];
		for (int j = 0; j < width; j++) norm[i][j] = new float[max_patchsize - min_patchsize + 1];
	}
}
//---------------------------------------------------------------------------



// fileInput.cpp handles the methods for file inputs
// Author Craig Hunter


#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "util.h"


std::string g_SampleVideoDir; // Global Variable Sample Video Directory
std::string g_VideoOutPutDir; // Global Variable Video Output Directory
std::string g_DataModel_NormalBlink; // Global Variable NormalBlink Text Data
std::string g_DataModel_DeliberateBlink; // Global Variable DeliberateBlink Text Data




//@readInDirectory reads in the directories stored within the directory txt file
void readInDirectory() {
	std::string currentDir = currentWorkingDirectory();
	std::ifstream file("Directories.txt"); // Stores directories file
	if (file.is_open()) { // Validation, checks if file is open
		getline(file, g_SampleVideoDir);
		if (g_SampleVideoDir == "Directories") {
			getline(file, g_SampleVideoDir); // Stores line in global sampleVideoDIr
			getline(file, g_VideoOutPutDir); // Stores line in global VideoOutPutDir
			getline(file, g_DataModel_NormalBlink); // Stores line in global DataModel_NormalBlink
			getline(file, g_DataModel_DeliberateBlink); // Stores line in global DataModel DirberateBlink


			g_SampleVideoDir = currentDir + g_SampleVideoDir; 
			g_VideoOutPutDir = currentDir + g_VideoOutPutDir;
			g_DataModel_NormalBlink = currentDir + g_DataModel_NormalBlink;
			g_DataModel_DeliberateBlink = currentDir + g_DataModel_DeliberateBlink;

			std::replace(g_SampleVideoDir.begin(), g_SampleVideoDir.end(), '\\', '/');
			std::replace(g_VideoOutPutDir.begin(), g_VideoOutPutDir.end(), '\\', '/');
			std::replace(g_DataModel_DeliberateBlink.begin(), g_DataModel_DeliberateBlink.end(), '\\', '/');
			std::replace(g_DataModel_NormalBlink.begin(), g_DataModel_NormalBlink.end(), '\\', '/');
			std::cout << "\nDirectories.txt loaded Sucessfully\n" << std::endl;
		}
	}
}



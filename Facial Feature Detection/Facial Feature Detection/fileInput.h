// fileInput.h handles the methods for inputting files
// Author Craig Hunter
#include <string>
#ifndef fileInput_H
#define fileInput_H

extern std::string g_SampleVideoDir; // Global Variable Sample Video Directory
extern std::string g_VideoOutPutDir; // Global Variable Video Output Directory
extern std::string g_DataModel_NormalBlink; // Global Variable NormalBlink Text Data
extern std::string g_DataModel_DeliberateBlink; // Global Variable DeliberateBlink Text Data

void readInDirectory(); //@readInDirectory reads in the directories stored within the directory txt file

#endif // !fileInput_H
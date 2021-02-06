// Util.cpp contains useful methods
// Author Craig Hunter

#include <Windows.h>
#include <string>

using namespace std;
//@this method returns the current working directory that the soloution is stored within
std::string currentWorkingDirectory()
{
	char workingDir[1000];
	GetCurrentDirectoryA(1000, workingDir);
	return string(workingDir) + '\\';
}
// userInterface.cpp handles the methods for user interface
// Author Craig Hunter
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <string>
#include <cstring>
#include "fileInput.h"
#include "userInterface.h"
#include "preVideoProcessing.h"
#include "videoDM.h"
#include "DataModel.h"
#include "FullDataModel.h"
#include "EulerDistance.h"
#include "videoData.h"
#include "CosineSim.h"
#include "ZeroMeanCosineSim.h"

// userInterface.cpp handles the user Interface and calls the needed methods
// for preprocessing and running similarity comparasions to detect blinks
// @Author Craig Hunter
using namespace cv;
cv::VideoCapture testVideo; //Stores the testVideo

//@ this method handles the initial stage of the user interface(contains validation)
void mainMenu() {
	readInDirectory(); // Read in File Directories from Txt File.
	std::string userInput; // @userInput stores the user's menu choice

	std::cout << "[F]acial [A]ctivity [I]mage [R]ecognition\n" << std::endl;
	std::cout << "Choose from the list \n[1] Default Input Clip \n[2] Enter custom clip\n" << std::endl;
	std::cin >> userInput;

	// if statement is true, default test directory pre-loaded in, will be used.
	if (userInput == "1") {
		std::cout << "Default Selected" << std::endl;
	}
	else if (userInput == "2") { // if statement is true, user provides a directory which points to a video clip
		std::cout << "Enter the directory to the suggested clip" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, g_SampleVideoDir); // if 2 is selected, take in entire line of input (including spaces for new directory)
	}
	else { // if neither of options is true, recall Method
		std::cout << "Error - Unexpected Input: Please try again" << std::endl;
		mainMenu();
	}
	loadVideo(); // Loading in VideoFile
}


// @ this method handles in loading the test Video for the user interface
void loadVideo() {
	try
	{
		
		#pragma warning(disable: 0)
		testVideo.open(g_SampleVideoDir); // VideoCapture object is loaded with Clip Directory
	}
	catch (const std::exception&)
	{
		// Validiation - if video file cannot be found, call mainmenu
		std::cout << "Error, Video Could not be found, try again" << std::endl;
		mainMenu();
	}

	preProcessVideo();

}

 //@ this method handles Preprocessing of the test Video for the user interface
void preProcessVideo() {

	if (testVideo.isOpened()) {
		// Convert Video to meet the starndards of low resolution, Greyscale and 25 FPS
		VideoProcessing(testVideo);
	}
	else {
		//Validiation technique
		std::cout << "Video Directory is not correct, please try again" << std::endl;
		mainMenu();
	}
	blinkDetection();

};


// @this method handles blink Detection of the test Video for the user interface
void blinkDetection() {
	std::string uInput;
	FullDataModel Normal_Blink(g_DataModel_NormalBlink);
	FullDataModel Deliberate_Blink(g_DataModel_DeliberateBlink);


	VideoDM vClip(g_VideoOutPutDir); // Creating testClip instance (which takes in 11 Frames)
	VideoDM vClip2(g_VideoOutPutDir); // Creating 2nd testClip instance
	

	std::cout << "\nWhat Detection Algorthium would you like to use?\n[1]Euler\n[2]Cosine Similarity\n[3]ZNCC" << std::endl;
	std::cin >> uInput;
	// Pick Comparasion Method
	
	if (uInput == "1") {
		eulerDis(vClip, Normal_Blink, Deliberate_Blink, g_vLength, 1);
		eulerDis(vClip2, Normal_Blink, Deliberate_Blink, g_vLength, 2);
	}
	else if (uInput == "2"){
		
		cosineSim(vClip, Normal_Blink, Deliberate_Blink, g_vLength, 1);
		cosineSim(vClip2, Normal_Blink, Deliberate_Blink, g_vLength, 2);
		
	}
	else if (uInput == "3") {
		ZeroMean(vClip, Normal_Blink, Deliberate_Blink, g_vLength, 1);
		ZeroMean(vClip2, Normal_Blink, Deliberate_Blink, g_vLength, 2);
	
	}
	else {

		std::cout << "Incorrect Output: Please Try Again" << std::endl;
		blinkDetection();

	}
}



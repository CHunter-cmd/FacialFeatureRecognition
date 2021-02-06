// PreVideoProcessing.cpp handles the methods for processing the video
// Author Craig Hunter

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include "greyScaleConversion.h"
#include <opencv2/opencv.hpp>
#include "videoData.h"
#include "fileInput.h"

int FPS;
int arr_Frame_Reduction[25];
int g_vLength;

void FrameReduction() {

	int* frame_Reduction = new int[FPS];
	int temp;

	// filling an array with incrementing numbers, each number represents a frame
	for (int i = 0; i < FPS; i++) {
		frame_Reduction[i] = i;
	}

	// Randomly shuffling the array
	std::random_shuffle(&frame_Reduction[0], &frame_Reduction[FPS]);

	// Filling main array with first 25 numbers, each number representing a frame
	for (int i = 0; i < 25; i++) {
		arr_Frame_Reduction[i] = frame_Reduction[i];
	}

	// Sorting the array, from smallest to largest
	for (int i = 0; i < 25; i++)
	{
		for (int j = i + 1; j < 25; j++)
		{
			if (arr_Frame_Reduction[i] > arr_Frame_Reduction[j])
			{
				temp = arr_Frame_Reduction[i];
				arr_Frame_Reduction[i] = arr_Frame_Reduction[j];
				arr_Frame_Reduction[j] = temp;
			}
		}
	}



}

void VideoProcessing(cv::VideoCapture sampleVideo) {
	// Calculating specfic video data
	FPS = getFramesPerSecond(sampleVideo);
	int totalFrames = getTotalFrames(sampleVideo);
	int totalVideoLength = getVideoLength(FPS, totalFrames);

	std::cout << "\n-Video Stats-" << std::endl;
	std::cout << "Video Length " << totalVideoLength << "s" << std::endl;
	std::cout << "FPS: " << FPS << std::endl;
	std::cout << "Total Frames: " << totalFrames << std::endl;
	g_vLength = totalVideoLength;



	std::string tempOutput, fileOutput; // Will store output directories
	BMPFrame obj_VideoFrame; // An instance of BMPFrame Object
	cv::Mat Frame; // Stores an indivdual frame of input Video

	FrameReduction(); // Reducing Frames to 25 per Second
	tempOutput = g_VideoOutPutDir + "temp.bmp";

	cv::Size size(64, 64);
	char BMP[1024];
	char TempBMPFile[1024];
	int counter = 1;

	sampleVideo >> Frame; // Pointing Frame to test Video;
	for (int Time = 0; Time <= (totalVideoLength - 1); Time++) {
	
		int Start = FPS * Time;
		int End = Start + (FPS);
		int Frame_Counter = 0;
		int Second_Frame_Counter = 0;

		for (int iFrame = Start; iFrame <= End; iFrame++) {

			if (arr_Frame_Reduction[Second_Frame_Counter] = Frame_Counter) {
				sampleVideo.set(cv::CAP_PROP_POS_FRAMES, iFrame);
				sampleVideo >> Frame;

				resize(Frame, Frame, size); // Reducing Resolution of image

				imwrite(tempOutput, Frame);

				strcpy_s(TempBMPFile, tempOutput.c_str());
				obj_VideoFrame.LoadImage(TempBMPFile);

				fileOutput = (g_VideoOutPutDir + "Frame" + to_string(counter) + ".bmp");
				strcpy_s(BMP, fileOutput.c_str());

				obj_VideoFrame.WriteImage(BMP); // Output bitmap image
				counter++;
				Second_Frame_Counter++;
			}
			Frame_Counter++;
		}
	}
	// Clean up temp files
	remove(TempBMPFile);
}

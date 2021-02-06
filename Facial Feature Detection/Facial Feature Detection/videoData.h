// videoData.h handles the methods for videoData.cpps
// Author Craig Hunter
#ifndef videoData_H
#define videoData_H

#include <opencv2/opencv.hpp>

int getTotalFrames(cv::VideoCapture input); //@getTotalFrames get total number of Frames in test Video

int getFramesPerSecond(cv::VideoCapture input); //@getFramesPerSecond get how many Frames per Second in test video

int getVideoLength(int FPS, int TFrames); //@getVideoLength get total video length in seconds of test video

#endif // !videoData_H

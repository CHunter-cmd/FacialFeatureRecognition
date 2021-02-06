// videoData.cpp handles gathering essential data about the test Video
// Author Craig Hunter
#include <opencv2/opencv.hpp>

//@getTotalFrames get total number of Frames in test Video
int getTotalFrames(cv::VideoCapture testVideo) {

	int totalFrameCount = 0; //Stores total number of frames
	cv::Mat frame; // stores a single frame


	while (true) {
		testVideo >> frame;
		if (frame.empty())
			break;
		totalFrameCount++;
	}

	return totalFrameCount; // Returns total number of frames
}

//@getFramesPerSecond get how many Frames per Second in test video
int getFramesPerSecond(cv::VideoCapture testVideo) {
	return testVideo.get(cv::CAP_PROP_FPS); // returns the Frames Per Second of test video
}

//@getVideoLength get total video length in seconds of test video
int getVideoLength(int FPS, int TFrames) {
	return(TFrames / FPS); //@ returns to the nearest second, total length of test Video
}
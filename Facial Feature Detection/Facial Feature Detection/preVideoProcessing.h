// PreVideoProcessing.h handles the methods for processing the video
// Author Craig Hunter
#ifndef preVideoProcessing_H
#define preVideoProcessing_H

#include <opencv2/opencv.hpp>

void FrameReduction();

void VideoProcessing(cv::VideoCapture sampleVideo);

extern int g_vLength; // Video Length


#endif // !preVideoProcessing_H#pragma once

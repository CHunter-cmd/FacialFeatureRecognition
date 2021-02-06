// CosineSim.h handles the methods for Cosine Similarity Comparasion
// Author Craig Hunter
#ifndef COSINESIM_H
#define COSINESIM_H

#include "FullDataModel.h"
#include "videoDM.h"

void cosineSim(VideoDM clip, FullDataModel NormalBlink, FullDataModel DeliberateBlink, int TotalFrames, int turn);


#endif // !COSINESIM_H


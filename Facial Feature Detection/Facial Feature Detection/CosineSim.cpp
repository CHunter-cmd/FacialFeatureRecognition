// CosineSim.cpp completes comparasions using CosineSim algor
// Author Craig Hunter

#include "CosineSim.h"
int tempcounterOne = 0;

//float dtw(VideoDM clip, FullDataModel blinkEvent, int FrameNum) {
//
//	float P_XY[50][50];   // Path matrix
//	float p_xy[50][50];  // matrix of item to item distance
//
//	int dtw[50][50];
//	int tmp_dtw0[100], tmp_dtw1[100];
//	int dtw0[100], dtw1[100];
//	float BIG = 100000;
//
//
//
//
//	int Ymin = 42, Ymax = 49, X = 45;
//
//
//	int datamodel_One[64][64];
//	int datamodel_Two[64][64];
//
//	for (int i = 0; i < 64; i++)
//		for (int x = 0; x < 64; x++) {
//			datamodel_One[i][x] = clip.image[FrameNum].data[i][x];
//			datamodel_Two[i][x] = blinkEvent.Model[0].image[FrameNum].data[i][x];
//		}
//
//
//
//	int w = abs(Ymax - X) + 1;  // add 1 here for equal length dtw (otherwise performing linear mapping)
//
//
//
//	for (int i = 0; i <= X; i++)
//		for (int j = 0; j <= Ymax; j++) {
//			float d = 0.;
//			for (int k = 0; k < 64; k++)
//				for (int l = 0; l < 64; l++) {
//					d = datamodel_One[k][l] - datamodel_Two[k][l];
//					//dis = d * d;
//				}
//			//p_xy[i][j] = sqrt(dis) / (64 * 64);
//			p_xy[i][j] = d;
//		}
//
//
//
//	// init
//	for (int i = 0; i <= X; i++)
//		for (int j = 0; j <= Ymax; j++) P_XY[i][j] = BIG;
//
//	P_XY[0][0] = p_xy[0][0]; dtw[0][0] = 0; // null
//	for (int i = 1; i <= w; i++)
//	{
//		P_XY[i][0] = P_XY[i - 1][0] + p_xy[i][0]; dtw[i][0] = 1;
//	} // horizontal
//	for (int j = 1; j <= w; j++)
//	{
//		P_XY[0][j] = P_XY[0][j - 1] + p_xy[0][j]; dtw[0][j] = 2;
//	} // vertical
//
//// recursion
//	for (int j = 1; j <= Ymax; j++) {
//		int i0 = j - w; if (i0 < 1) i0 = 1;
//		int i1 = j + w; if (i1 > X) i1 = X;
//		for (int i = i0; i <= i1; i++) {
//			float h = P_XY[i - 1][j] + p_xy[i][j];
//			float d = P_XY[i - 1][j - 1] + p_xy[i][j];
//			float v = P_XY[i][j - 1] + p_xy[i][j];
//			if (d < h && d < v)
//			{
//				P_XY[i][j] = d; dtw[i][j] = 3;
//			} // diagonal
//			else if (h < v)
//			{
//				P_XY[i][j] = h; dtw[i][j] = 1;
//			}
//			else { P_XY[i][j] = v; dtw[i][j] = 2; }
//			if ((h == d) && (d == v))
//			{
//				P_XY[i][j] = d; dtw[i][j] = 3;
//			}
//		}
//	}
//
//	// best path, normalization, best warp within u+rmin ~ u+rmax
//	float Q = BIG; int J, L;
//	for (int j0 = Ymin; j0 <= Ymax; j0++) {
//		// path backtracking
//		int i = X, j = j0, l = 0;
//		tmp_dtw0[l] = i; tmp_dtw1[l] = j;
//		while (i > 0 || j > 0) {
//			l++;
//			if (dtw[i][j] == 1)
//			{
//				i -= 1;
//			}
//			else if (dtw[i][j] == 2)
//			{
//				j -= 1;
//			}
//			else if (dtw[i][j] == 3)
//			{
//				i -= 1; j -= 1;
//			}
//
//			tmp_dtw0[l] = i; tmp_dtw1[l] = j;
//		}
//
//		// number-of-local-distances based normalization
//		P_XY[X][j0] *= (float)(X + 1) / (float)(l + 1);
//
//		// best warp
//		if (P_XY[X][j0] <= Q) {
//
//			Q = P_XY[X][j0];
//			J = j0;
//			L = l;
//
//			return fabs(Q);
//		}
//	}
//
//	return Q;
//}



double CoSim(double* imageOne, double* imageTwo, double length)
{
	double mul = 0.0;
	double totalImageOne = 0.0;
	double totalImageTwo = 0.0;
	double output = 0.0;

	for (int i = 0; i < length; ++i)
	{
		mul += imageOne[i] * imageTwo[i];
		totalImageOne += imageOne[i] * imageOne[i];
		totalImageTwo += imageTwo[i] * imageTwo[i];
	}

	return (mul / (sqrt(totalImageOne) * sqrt(totalImageTwo)));
}

void cosineSim(VideoDM clip, FullDataModel NormalBlink, FullDataModel DeliberateBlink, int TotalFrames, int turn) {
	double AcceptRate = 98.18;
	double TotalCosine = 0;
	int FrameCounter = 0;
	TotalFrames = TotalFrames * 25;

	AcceptRate = AcceptRate / 10;


	for (int i = 0; i < (TotalFrames - 12); i++) {

		for (int x = 0; x < 10; x++) {


			double normal_blink_array[4096];
			double deliberate_blink_array[4096];
			double videoClip[4096];
			int arrayCounter = 0;

			for (int y = 0; y < 64; y++) {
				for (int z = 0; z < 64; z++) {
					videoClip[arrayCounter] = clip.image[x].data[y][z];
					normal_blink_array[arrayCounter] = NormalBlink.Model[0].image[x].data[y][z];
					deliberate_blink_array[arrayCounter] = DeliberateBlink.Model[0].image[x].data[y][z];
					arrayCounter++;
				}
			}

			if (turn == 1) {
				TotalCosine = TotalCosine + CoSim(videoClip, normal_blink_array, 4096);
			}
			if (turn == 2) {
				TotalCosine = TotalCosine + CoSim(videoClip, deliberate_blink_array, 4096);
			}
		}

		FrameCounter++;
		if (turn == 1) {
			
			if (TotalCosine >= AcceptRate)
			{
				cout << "Normal Blink Detected at " << (FrameCounter) << " to " << (FrameCounter + 11) << endl;
			}
		}
		else {
			
			if (TotalCosine >= AcceptRate)
			{

				cout << "Deliberate Blink Detected at " << (FrameCounter) << " to " << (FrameCounter + 11) << endl;
			}


		}
		clip.IncreaseByOne();
		TotalCosine = 0;

	}
}
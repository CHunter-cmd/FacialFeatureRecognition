// EulerDistance handles the methods for EulerDistance Comparasions
// Author Craig Hunter
#include "EulerDistance.h"
#include "videoDM.h"

int detection = 0;
int tempcounter = 0;

float dtw(VideoDM clip, FullDataModel blinkEvent, int FrameNum) {

	float P_XY[50][50];   // Path matrix
	float p_xy[50][50];  // matrix of item to item distance

	int dtw[50][50];
	int tmp_dtw0[100], tmp_dtw1[100];
	int dtw0[100], dtw1[100];
	float BIG = 100000;


	float x[] = { 1, 2, 2, 2, 3, 4, 4, 5, 5 };
	float y[] = { 1, 2, 2, 3, 3, 4, 5, 6, 6, 7, 7, 8 };

	int Ymin = 42, Ymax = 49, X = 45 ;






	int w = abs(Ymax - X) + 1;  // add 1 here for equal length dtw (otherwise performing linear mapping)


	for (int i = 0; i <= X; i++)
		for (int j = 0; j <= Ymax; j++) p_xy[i][j] = fabs(x[i] - y[j]);



	// init
	for (int i = 0; i <= X; i++)
		for (int j = 0; j <= Ymax; j++) P_XY[i][j] = BIG;

	P_XY[0][0] = p_xy[0][0]; dtw[0][0] = 0; // null
	for (int i = 1; i <= w; i++)
	{
		P_XY[i][0] = P_XY[i - 1][0] + p_xy[i][0]; dtw[i][0] = 1;
	} // horizontal
	for (int j = 1; j <= w; j++)
	{
		P_XY[0][j] = P_XY[0][j - 1] + p_xy[0][j]; dtw[0][j] = 2;
	} // vertical

// recursion
	for (int j = 1; j <= Ymax; j++) {
		int i0 = j - w; if (i0 < 1) i0 = 1;
		int i1 = j + w; if (i1 > X) i1 = X;
		for (int i = i0; i <= i1; i++) {
			float h = P_XY[i - 1][j] + p_xy[i][j];
			float d = P_XY[i - 1][j - 1] + p_xy[i][j];
			float v = P_XY[i][j - 1] + p_xy[i][j];
			if (d < h && d < v)
			{
				P_XY[i][j] = d; dtw[i][j] = 3;
			} // diagonal
			else if (h < v)
			{
				P_XY[i][j] = h; dtw[i][j] = 1;
			}
			else { P_XY[i][j] = v; dtw[i][j] = 2; }
			if ((h == d) && (d == v))
			{
				P_XY[i][j] = d; dtw[i][j] = 3;
			}
		}
	}

	// best path, normalization, best warp within u+rmin ~ u+rmax
	float Q = BIG; int J, L;
	for (int j0 = Ymin; j0 <= Ymax; j0++) {
		// path backtracking
		int i = X, j = j0, l = 0;
		tmp_dtw0[l] = i; tmp_dtw1[l] = j;
		while (i > 0 || j > 0) {
			l++;
			if (dtw[i][j] == 1)
			{
				i -= 1;
			}
			else if (dtw[i][j] == 2)
			{
				j -= 1;
			}
			else if (dtw[i][j] == 3)
			{
				i -= 1; j -= 1;
			}

			tmp_dtw0[l] = i; tmp_dtw1[l] = j;
		}

		// number-of-local-distances based normalization
		P_XY[X][j0] *= (float)(X + 1) / (float)(l + 1);

		// best warp
		if (P_XY[X][j0] <= Q) {

			Q = P_XY[X][j0];
			J = j0;
			L = l;
			
			return fabs(Q);
		}
	}
	
	return Q;
}



















void eulerDis(VideoDM clip, FullDataModel NormalBlink, FullDataModel DeliberateBlink, int TotalFrames, int turn) {
	int TotalDistance = 0;
	int FrameCounter = 0;
	int FrameHolder[11];
	double AcceptRate = 1.66;
	
	AcceptRate = AcceptRate * 10000;
	TotalFrames = TotalFrames * 25;

	for (int i = 0; i < (TotalFrames - 12); i++) {

		for (int x = 0; x < 10; x++) {

			if (turn == 1) {

				for (int z = 0; z < 64; z++)
					for (int y = 0; y < 64; y++)
					{
						
						TotalDistance = ((clip.image[x].data[z][y]) - NormalBlink.Model[0].image[x].data[z][y]) + TotalDistance;
					}

				FrameHolder[x] = TotalDistance;

			}
			else{
				for (int z = 0; z < 64; z++)
					for (int y = 0; y < 64; y++) {
				
						TotalDistance = ((clip.image[x].data[z][y]) - DeliberateBlink.Model[0].image[x].data[z][y]) + TotalDistance;
					}
				
		}
	
			
		}
		FrameCounter++;
		if (turn == 1) {
			TotalDistance = abs(TotalDistance);
			cout.precision(17);
			if (TotalDistance  <= AcceptRate)
			{    
				cout << "Normal Blink Detected at " << (FrameCounter) << " to " << (FrameCounter + 11) << endl;
				detection++;
				
			}
		}
		else {
			TotalDistance = abs(TotalDistance);
			
			if (TotalDistance <= AcceptRate)
			{
				cout << "Deliberate Blink Detected at " << (FrameCounter) << " to " << (FrameCounter + 11) << endl;
				detection++;
			} 
		
		
		}
		clip.IncreaseByOne();
		TotalDistance = 0;
	}

	if (detection == 0) {
		if (turn = 2)
		cout << "No Blinks Detection" << endl;
	}

}
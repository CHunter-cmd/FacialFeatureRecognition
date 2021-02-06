// DCT.cpp handles the methods for image compression
// Author Craig Hunter & Unknown
#include <math.h>

double DCT(double bitmapInput[64][64], int M, int N, double DCTOutput[64][64]) {

	float pi = 3.1415926;

	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {
			DCTOutput[m][n] = 0.;
			for (int i = 0; i < M; i++) {
				float a = cos(pi * (i + 0.5) * m / M);
				for (int j = 0; j < N; j++)
					DCTOutput[m][n] += bitmapInput[i][j] * a * cos(pi * (j + 0.5) * n / N);
			}
		}
	}
	return 0.0;
}
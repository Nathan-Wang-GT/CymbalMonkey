#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;

double goertzel_FFT(double* data, double k, int N) {
	
	double omega = 2.0 * M_PI * k / (double) N;
	double cr = cos(omega * M_PI / 180.0);
	double ci = sin(omega * M_PI / 180.0);
	double coeff = 2.0 * cr;
	double sprev = 0.0;
	double sprev2 = 0.0;

	for (int i = 0; i < N - 1; i++) {
		double s = data[i] + coeff * sprev - sprev2;
		sprev2 = sprev;
		sprev = s;
	}

	double It = cr * sprev - sprev2;
	double Qt = ci * sprev;

	double omega2 = 2.0 * M_PI * k;
	double cr2 = cos(omega2 * M_PI / 180.0);
	double ci2 = sin(omega2 * M_PI / 180.0);

	double I = It * cr2 + Qt * ci2;
	double Q = -It * ci2 + Qt * cr2;

	return sqrt(I * I + Q * Q);
}
// GoertzelSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
//#include "AudioFile.h"
#include <fstream>
#include <string>
using namespace std;

double goertzel_FFT(double* data, double k, int N) {

	double omega = 2.0 * M_PI * k / (double)N;
	double cr = cos(omega);
	double ci = sin(omega);
	double coeff = 2.0 * cr;
	double sprev = 0.0;
	double sprev2 = 0.0;

	for (int i = 0; i < N - 1; ++i) {
		double s = data[i] + coeff * sprev - sprev2;
		sprev2 = sprev;
		sprev = s;
	}

	double It = cr * sprev - sprev2;
	double Qt = ci * sprev;

	double omega2 = 2.0 * M_PI * k;
	double cr2 = cos(omega2);
	double ci2 = sin(omega2);

	double I = It * cr2 + Qt * ci2;
	double Q = -It * ci2 + Qt * cr2;

	return sqrt(I * I + Q * Q);
}





int main()
{
	ifstream file("C:/GT/GT Semesters/4th Year 1st Semester/Senior Design/DSP Simulation/C.txt");

	ifstream ffile("C:/GT/GT Semesters/4th Year 1st Semester/Senior Design/DSP Simulation/F.txt");

	double data[10000];

	double dataF[10000];

	int counter = 0;

	//double value;

	string str;
	while (getline(file, str)) {


		//cout << str << endl;
		data[counter] = stod(str);

		//cout << data[counter] << endl;
		counter++;

	}

	counter = 0;
	while (getline(ffile, str)) {
		dataF[counter] = stod(str);
		counter++;
	}

	double freq = 698.4565;

	double bin = 2 * freq / 44100 * 10000;
	double power = goertzel_FFT(data, bin, 10000);

	cout << power << endl;

	double powerF = goertzel_FFT(dataF, bin, 10000);

	cout << powerF << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

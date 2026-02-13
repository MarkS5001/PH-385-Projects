/*
PH 385 Project 5 Main File

Simulates the motion of a string including dampening, and stiffness.

The user inputs the wave speed for the medium, length of each segment,
how many segments, cromer value (r), dampening coefficient, duration,
stiffness, and parameters for a Gaussian wave function (center, width,
and amplitude), all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/13/2026
*/
#include <iostream>
#include <ctime>
#include "WaveString.cpp"

double length = 1.0; // In m
double waveSpeed = 250.0; // In m/s
double segmentLength = 0.01; // In m
int segments = 100;
double r = 0.1; // Timestep ratio
double dampeningCoefficient = 10.0;
double duration = 0.25; // s

// Parameters for 1st Gaussian all in meters
double center1 = 0.5, width1 = 0.1, amplitude1 = 0.01;

// Parameters for 2nd Gaussian all in meters
double center2 = 0.35, width2 = 0.05, amplitude2 = 0.01;

// Parameters for 3rd Gaussian all in meters
double center3 = 0.75, width3 = 0.03, amplitude3 = -0.01;

double stiffness001 = 1e-3;
std::string filename001 = "resultsP5_1e-3.txt";

double stiffness0001 = 1e-4;
std::string filename0001 = "resultsP5_1e-4.txt";

double stiffness00001 = 1e-5;
std::string filename00001 = "resultsP5_1e-5.txt";

double stiffness000001 = 1e-6;
std::string filename000001 = "resultsP5_1e-6.txt";

using namespace std;

int main()
{
    clock_t start = clock(); // Get program start time

    // Stiffness of 1e-3
    // Initialize string
    WaveString waveString001(segments, segmentLength, stiffness001, duration, waveSpeed, r, dampeningCoefficient, filename001);

    // Add waves to string
    waveString001.AddWave(amplitude1, width1, center1);
    waveString001.AddWave(amplitude2, width2, center2);
    waveString001.AddWave(amplitude3, width3, center3);

    // Start calculation
    waveString001.CalculateStringPosition();

    // Stiffness of 1e-4
    // Initialize string
    WaveString waveString0001(segments, segmentLength, stiffness0001, duration, waveSpeed, r, dampeningCoefficient, filename0001);

    // Add waves to string
    waveString0001.AddWave(amplitude1, width1, center1);
    waveString0001.AddWave(amplitude2, width2, center2);
    waveString0001.AddWave(amplitude3, width3, center3);

    // Start calculation
    waveString0001.CalculateStringPosition();

    // Stiffness of 1e-5
    // Initialize string
    WaveString waveString00001(segments, segmentLength, stiffness00001, duration, waveSpeed, r, dampeningCoefficient, filename00001);

    // Add waves to string
    waveString00001.AddWave(amplitude1, width1, center1);
    waveString00001.AddWave(amplitude2, width2, center2);
    waveString00001.AddWave(amplitude3, width3, center3);

    // Start calculation
    waveString00001.CalculateStringPosition();

    // Stiffness of 1e-6
    // Initialize string
    WaveString waveString000001(segments, segmentLength, stiffness000001, duration, waveSpeed, r, dampeningCoefficient, filename000001);

    // Add waves to string
    waveString000001.AddWave(amplitude1, width1, center1);
    waveString000001.AddWave(amplitude2, width2, center2);
    waveString000001.AddWave(amplitude3, width3, center3);

    // Start calculation
    waveString000001.CalculateStringPosition();

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
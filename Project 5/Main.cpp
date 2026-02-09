/*
PH 385 Project 1 Main File

Models the projectile motion of a ball in three dimensions, including
quadratic air resistance and the Magnus force.

The user inputs the mass of the ball, diameter of the ball, air density, drag
coefficient, initial position, initial velocity, spin angular velocity,
and time step, all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/9/2026
*/
#include <iostream>
#include <ctime>
#include "WaveString.hpp"

double length = 1.0; // In m
double waveSpeed = 250.0; // In m/s
int segments = 100;
double r = 1.0; // Timestep ratio
double stiffness = 0.001;
double dampeningCoefficient = 10.0;
double duration = 0.25; // s

// Parameters for 1st Gaussian all in meters
double center1 = 0.5, width1 = 0.1, amplitude1 = 0.01;

// Parameters for 2nd Gaussian all in meters
double center2 = 0.35, width2 = 0.05, amplitude2 = 0.01;

// Parameters for 3rd Gaussian all in meters
double center3 = 0.75, width3 = 0.03, amplitude3 = 0.01;

using namespace std;

int main()
{
    clock_t start = clock(); // Get program start time

    

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
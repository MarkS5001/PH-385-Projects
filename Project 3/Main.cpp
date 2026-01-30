/*
PH 385 Project 3 Main File

Models the motion of a three body gravitational system.

The user inputs the mass of the ball, diameter of the ball, air density, drag
coefficient, initial position, initial velocity, spin angular velocity,
and time step, all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/26/2026
*/

#include <iostream>
#include "CelestialSystem.cpp"
#include "CelestialObject.cpp"

using namespace CS;

// Masses of interested objects
double sunMass = 1;
double earthMass = 3.0027e-6;
double jupiterMass = 9.54588e-4*1000.0;

// Initial positions of interested objects
double sunRadiusX = 0.0, sunRadiusY = 0.0;
double earthRadiusX = 1.0, earthRadiusY = 0.0;
double jupiterRadiusX = -5.2, jupiterRadiusY = 0.0;

// Initial velocities of interested objects
double sunVelocityX = 0.0, sunVelocityY = 0.0;
double earthVelocityX = 0.0, earthVelocityY = 2*3.1415;
double jupiterVelocityX = 0.0, jupiterVelocityY = -0.876897*3.1415;

// Duration for length of simulation
double duration = 11.7;

// Step time step
double timeStep = 0.0003;

// Set filename
std::string filename = "resultsP3.txt";

int main()
{
    // Initialize system
    CelestialSystem systemOfInterest(timeStep, duration, filename);

    // Add the objects of the system
    systemOfInterest.AddCelestialObject(sunMass, sunRadiusX, sunRadiusY, sunVelocityX, sunVelocityY);
    systemOfInterest.AddCelestialObject(earthMass, earthRadiusX, earthRadiusY, earthVelocityX, earthVelocityY);
    systemOfInterest.AddCelestialObject(jupiterMass, jupiterRadiusX, jupiterRadiusY, jupiterVelocityX, jupiterVelocityY);

    systemOfInterest.VerletMethod();

    // Plot the data after running 
    // system("gnuplot -persistent plot.gp");

    return 0;
}
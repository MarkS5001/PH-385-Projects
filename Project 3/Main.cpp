/*
PH 385 Project 3 Main File

Models the motion of a three body gravitational system.

The user inputs the mass of the objects, their distance (x and y), their velocity (x and y),
duration (in years), and time step (in years), unless otherwise noted all in SI units. 
This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/30/2026
*/

#include <iostream>
#include <ctime>
#include "CelestialSystem.cpp"
#include "CelestialObject.cpp"

using namespace CS;

// Masses of interested objects
double sunMass = 1;
double earthMass = 3.0027e-6;
double jupiterMass = 9.54588e-4;

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
std::string filename1 = "resultsP3_1.txt";
std::string filename10 = "resultsP3_10.txt";
std::string filename100 = "resultsP3_100.txt";
std::string filename1000 = "resultsP3_1000.txt";

int main()
{
    clock_t start = clock(); // Get program start time

    // Initialize system for jupiter mass normal
    CelestialSystem systemOfInterest1(timeStep, duration, filename1);

    // Add the objects of the system
    systemOfInterest1.AddCelestialObject(sunMass, sunRadiusX, sunRadiusY, sunVelocityX, sunVelocityY);
    systemOfInterest1.AddCelestialObject(earthMass, earthRadiusX, earthRadiusY, earthVelocityX, earthVelocityY);
    systemOfInterest1.AddCelestialObject(jupiterMass, jupiterRadiusX, jupiterRadiusY, jupiterVelocityX, jupiterVelocityY);

    systemOfInterest1.VerletMethod();

    // Initialize system for jupiter mass 10 times normal
    CelestialSystem systemOfInterest10(timeStep, duration, filename10);

    // Add the objects of the system
    systemOfInterest10.AddCelestialObject(sunMass, sunRadiusX, sunRadiusY, sunVelocityX, sunVelocityY);
    systemOfInterest10.AddCelestialObject(earthMass, earthRadiusX, earthRadiusY, earthVelocityX, earthVelocityY);
    systemOfInterest10.AddCelestialObject(jupiterMass*10.0, jupiterRadiusX, jupiterRadiusY, jupiterVelocityX, jupiterVelocityY);

    systemOfInterest10.VerletMethod();

    // Initialize system for jupiter mass 100 times normal
    CelestialSystem systemOfInterest100(timeStep, duration, filename100);

    // Add the objects of the system
    systemOfInterest100.AddCelestialObject(sunMass, sunRadiusX, sunRadiusY, sunVelocityX, sunVelocityY);
    systemOfInterest100.AddCelestialObject(earthMass, earthRadiusX, earthRadiusY, earthVelocityX, earthVelocityY);
    systemOfInterest100.AddCelestialObject(jupiterMass*100.0, jupiterRadiusX, jupiterRadiusY, jupiterVelocityX, jupiterVelocityY);

    systemOfInterest100.VerletMethod();

    // Initialize system for jupiter mass 1000 times normal
    CelestialSystem systemOfInterest1000(timeStep, duration, filename1000);

    // Add the objects of the system
    systemOfInterest1000.AddCelestialObject(sunMass, sunRadiusX, sunRadiusY, sunVelocityX, sunVelocityY);
    systemOfInterest1000.AddCelestialObject(earthMass, earthRadiusX, earthRadiusY, earthVelocityX, earthVelocityY);
    systemOfInterest1000.AddCelestialObject(jupiterMass*1000.0, jupiterRadiusX, jupiterRadiusY, jupiterVelocityX, jupiterVelocityY);

    systemOfInterest1000.VerletMethod();

    // Plot the data after running 
    // system("gnuplot -persistent plot.gp");

    time_t end = clock();// Get program start time
    std::cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
/*
PH 385 Project 3 Main File

Models the motion of a three body gravitational system.

The user inputs the mass of the ball, diameter of the ball, air density, drag
coefficient, initial position, initial velocity, spin angular velocity,
and time step, all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/26/2026
*/

// Masses of interested objects
double sunMass = 1;
double earthMass = 3.0027e-6;
double jupiterMass = 9.54588e-4;

// Initial positions of interested objects
double sunRadiusX = 0.0, sunRadiusY = 0.0;
double EarthRadiusX = 1.0, EarthRadiusY = 0.0;
double jupiterRadiusX = -5.2, jupiterRadiusY = 0.0;

// Initial velocities of interested objects
double sunVelocityX = 0.0, sunVelocityY = 0.0;
double EarthVelocityX = 1.0, EarthVelocityY = 2*3.1415;
double jupiterVelocityX = -5.2, jupiterVelocityY = 0.876897*3.1415;


void main()
{
    
    // Plot the data after running 
    // system("gnuplot -persistent PingPong_Plot.gp");
}
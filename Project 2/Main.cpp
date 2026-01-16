/*
PH 385 Project 1 Main File

Models the projectile motion of a ball in three dimensions, including
quadratic air resistance and the Magnus force.

The user inputs the mass of the ball, diameter of the ball, air density, drag
coefficient, initial position, initial velocity, spin angular velocity,
and time step, all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/14/2026
*/

#include <iostream>
#include <vector>
#include "PingPong.cpp"
// #include <cstdlib> // Library to have gnuplot plot the data after running
using namespace std;

// Initial variables
double mass;
double length;
double dampingCoefficient;
double initialAngle;
double initialAngularVelocity;
double duration;
double timeStep;
double drivingForce;
double drivingFrequency;

void main()
{

    // Plot the data after running 
    // system("gnuplot -persistent PingPong_Plot.gp");
}
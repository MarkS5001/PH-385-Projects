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
#include "Pendulum.cpp"
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
    DrivenPendulum pend(1, 9.8, 0.5, 0.2, 0, 180, 0.01, 1.2, 0.66, "resultsP2.txt");

    pend.RungeKutta();
    
    // Plot the data after running 
    system("gnuplot -persistent plot.gp");
}
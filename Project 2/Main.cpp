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
// double mass;
// double length;
// double dampingCoefficient;
// double initialAngle;
// double initialAngularVelocity;
// double duration;
// double timeStep;
// double drivingForce;
// double drivingFrequency;
// string filename;

// Variables for testing
double mass = 1;
double length = 9.8;
double dampingCoefficient = 0.5;
double initialAngle = 0.2;
double initialAngularVelocity = 0.0;
double duration = 180;//60;
double timeStep = 0.0004;
double drivingForce = 1.2;
double drivingFrequency = 2.0/3.0;
string filename = "resultsP2.txt";

void main()
{
    DrivenPendulum pend(mass,
                        length,
                        dampingCoefficient,
                        initialAngle,
                        initialAngularVelocity,
                        duration,
                        timeStep,
                        drivingForce,
                        drivingFrequency,
                        filename);

    pend.RungeKutta();
    
    // Plot the data after running 
    system("gnuplot -persistent plot.gp");
}
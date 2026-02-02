/*
PH 385 Project 2 Main File

Models a physical pendulum with a driving force, and dampening

The user inputs the mass, length, dampening coefficient, initial angle,
initial angular velocity, duration, time step, magnitude of driving force,
and driving frequency, all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/23/2026
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
string filename;

// Variables for testing
// double mass = 1;
// double length = 9.8;
// double dampingCoefficient = 0.5;
// double initialAngle = 0.2;
// double initialAngularVelocity = 0.0;
// double duration = 72000;//60;
// double timeStep = 0.0004;
// double drivingForce = 1.2;
// double drivingFrequency = 2.0/3.0;
// string filename = "resultsP2.txt";

int main()
{
    // Get the user input

    cout << "What is the mass of the pendulum in kg? ";
    cin >> mass;

    cout << "What is the length of the pendulum in m? ";
    cin >> length;

    cout << "What is the dampening coefficient? ";
    cin >> dampingCoefficient;

    cout << "What is the initial angle? ";
    cin >> initialAngle;

    cout << "What is the initial angular velocity? ";
    cin >> initialAngularVelocity;

    cout << "How long do you want the pendulum to run? ";
    cin >> duration;

    cout << "What is the time step? ";
    cin >> timeStep;

    cout << "What is the magnitude of the driving force? ";
    cin >> drivingForce;

    cout << "What is the driving frequency? ";
    cin >> drivingFrequency;    

    cout << "What filename will it be saved to? ";
    cin >> filename;

    // Send initial variables
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
    // Start simulation
    pend.RungeKutta();
    
    // Plot the data after running 
    // system("gnuplot -persistent plot.gp");

    return 0;
}
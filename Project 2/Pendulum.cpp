/*
Class Pendulum

Simulates the motion of a physical pendulum with a driving force, 
and dampening

This code has limitations in the form of time step. This program uses
Runge-Kutta of fourth order, which means it can't predict with 5th order accuracy.
Depending on what the time step is as well changes the starting point for a theta vs time plot
just a little.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/23/2026
*/

#include "Pendulum.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace Pendulum;

// Constructor to initialize the values
DrivenPendulum::DrivenPendulum(const double Mass,
                                const double Length,
                                const double DampingCoefficient,
                                const double InitialAngle,
                                const double InitialAngularVelocity,
                                const double Duration,
                                const double TimeStep,
                                const double DrivingForce,
                                const double DrivingFrequency,
                                const string& Filename)
                                :
                                mass(Mass),
                                length(Length),
                                dampingCoefficient(DampingCoefficient),
                                duration(Duration),
                                timeStep(TimeStep),
                                drivingForce(DrivingForce),
                                drivingFrequency(DrivingFrequency),
                                filename(Filename),
                                theta(InitialAngle),
                                omega(InitialAngularVelocity),
                                time(0)
                                {};
                               
// Equation to update omega
double DrivenPendulum::PhysicalPendulum(double currentTheta, double currentOmega, double currentTime)
{
    return -g/length*sin(currentTheta)-dampingCoefficient*currentOmega+drivingForce*sin(drivingFrequency*currentTime);
};

// Equation to update theta
double DrivenPendulum::Theta(double currentOmega)
{
    return currentOmega;
};

// Runge-Kutta loop
void DrivenPendulum::RungeKutta()
{
    // Initialize file handling
    ofstream Position(filename); 

    while(time < duration)
    {
        // Update values using RK4
        // The equation for theta is time-independent. It also just returns omega so the function could not be called.
        // It is left in however to show that it is updated the same.
        k1o = timeStep*PhysicalPendulum(theta, omega, time);
        k1t = timeStep*Theta(omega);

        k2o = timeStep*PhysicalPendulum(theta+0.5*k1t, omega+0.5*k1o, time+0.5*timeStep);
        k2t = timeStep*Theta(omega+0.5*k1o);

        k3o = timeStep*PhysicalPendulum(theta+0.5*k2t, omega+0.5*k2o, time+0.5*timeStep);
        k3t = timeStep*Theta(omega+0.5*k2o);

        k4o = timeStep*PhysicalPendulum(theta+k3t, omega+k3o, time+timeStep);
        k4t = timeStep*Theta(omega+k3o);

        omega += (k1o+2*k2o+2*k3o+k4o)/6;        
        theta += (k1t+2*k2t+2*k3t+k4t)/6;
        time += timeStep;

        if (theta < -3.1415)
        {
            theta += 2*3.1415;
        } else if (theta > 3.1415)
        {
            theta -= 2*3.1415;
        };

        // Write values to file. Commented and uncommented depending on what is needed.

        // Position << theta << "," << omega << "\n";

        // if (sin(time*drivingFrequency-3.1415/2.0) < 0 && sin((time+timeStep)*drivingFrequency-3.1415/2.0) >= 0)
        // {
        //     Position << theta << "," << omega << "\n";
        // };

        if (sin(time*drivingFrequency-3.1415/4.0) < 0 && sin((time+timeStep)*drivingFrequency-3.1415/4.0) >= 0)
        {
            Position << theta << "," << omega << "\n";
        };
    }
    Position.close();
};
/*
Class PingPong

Simulates the projectile motion of a ball including quadratic air
resistance, and the Magnus force using Euler's method.

This code has limitations in the form of time step. With the use of Euler's
method, h (the time step) squared terms are neglected, and these terms will add up.
You can also decrease the time step to decrease the error, however the number
of steps needed will increase if a user does this.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/14/2026
*/

#include "Pendulum.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace Pendulum;

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
                                omega(InitialAngularVelocity)
                                {};
                                
double DrivenPendulum::PhysicalPendulum(double currentTheta, double currentOmega)
{
    return (-g/length*sin(currentTheta)-dampingCoefficient*currentOmega+drivingForce*sin(drivingFrequency*time))*timeStep;
};

double DrivenPendulum::Theta(double currentOmega)
{
    return currentOmega*timeStep;
};

void DrivenPendulum::RungeKutta()
{
    // Initialize file handling
    ofstream Position(filename); 
    Position << theta << "," << omega << "," << time << "\n"; // Write initial values to file

    while(time < duration)
    {
        // Update values using RK4
        k1 = timeStep*PhysicalPendulum(omega, time);
        k2 = timeStep*PhysicalPendulum(omega+0.5*k1, time+0.5*timeStep);
        k3 = timeStep*PhysicalPendulum(omega+0.5*k2, time+0.5*timeStep);
        k4 = timeStep*PhysicalPendulum(omega+k3, time+timeStep);
        omega += (k1+2*k2+2*k3+k4)/6;

        k1 = timeStep*PhysicalPendulum(theta, time);
        k2 = timeStep*PhysicalPendulum(theta+0.5*k1, time+0.5*timeStep);
        k3 = timeStep*PhysicalPendulum(theta+0.5*k2, time+0.5*timeStep);
        k4 = timeStep*PhysicalPendulum(theta+k3, time+timeStep);
        theta += omega*timeStep;
        time += timeStep;

        // Write values to file
        Position << theta << "," << omega << "," << time << "\n"; 
    }
    Position.close();
};
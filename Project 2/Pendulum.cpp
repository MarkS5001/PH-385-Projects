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
                                
double DrivenPendulum::PhysicalPendulum(double currentTheta, double currentOmega, double currentTime)
{
    return -g/length*sin(currentTheta)-dampingCoefficient*currentOmega+drivingForce*sin(drivingFrequency*currentTime);
};

double DrivenPendulum::Theta(double currentOmega)
{
    return currentOmega;
};

// double DrivenPendulum::RK4(double currentTheta, double currentOmgea, double currentTime, double timestep, std::function<double(double, double, double)> Func)
// {
//     double delta[2];
//     delta[0] = omega;
//     delta[1] = Func(currentTheta, currentOmgea, currentTime);
// };

void DrivenPendulum::RungeKutta()
{
    // Initialize file handling
    ofstream Position(filename); 
    Position << theta << "," << omega << "," << time << "\n"; // Write initial values to file

    while(time < duration)
    {
        // Update values using RK4
        // Omega first
        k1o = timeStep*PhysicalPendulum(theta, omega, time);
        k2o = timeStep*PhysicalPendulum(theta, omega+0.5*k1o, time+0.5*timeStep);
        k3o = timeStep*PhysicalPendulum(theta, omega+0.5*k2o, time+0.5*timeStep);
        k4o = timeStep*PhysicalPendulum(theta, omega+k3o, time+timeStep);
        
        // Now theta 
        // The equation is time-independent. It also just returns omega so the function could not be called.
        // It is left in however to show that it is updated the same.
        k1t = timeStep*Theta(omega);
        k2t = timeStep*Theta(omega+0.5*k1t);
        k3t = timeStep*Theta(omega+0.5*k2t);
        k4t = timeStep*Theta(omega+k3t);

        omega += (k1o+2*k2o+2*k3o+k4o)/6;        
        theta += (k1t+2*k2t+2*k3t+k4t)/6;
        time += timeStep;

        // Write values to file
        Position << theta << "," << omega << "," << time << "\n"; 
    }
    Position.close();
};
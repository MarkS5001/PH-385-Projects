/*
Class CelestialSystem

Simulates the motion of a multi-body system. Assumes the first object in system is stationary.

This code has limitations in the form of time step. With the use of Euler's
method, h (the time step) squared terms are neglected, and these terms will add up.
You can also decrease the time step to decrease the error, however the number
of steps needed will increase if a user does this.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/26/2026
*/

#include "CelestialSystem.hpp"
#include "CelestialObject.cpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace CS;

// CelestialSystem::CelestialSystem(int amount)
// {
//     for (int i = 0; i < amount; i++)
//     {
//         double mass;
//         double radius;
//         double velocity;

//         CelestialObject currentCelestialObject(mass, radius, velocity);

//         celestialObjects.push_back(currentCelestialObject);
//     }
// }

// Initialize parameters
CelestialSystem::CelestialSystem(double TimeStep) : timeStep(TimeStep){};

// Method to add the various celestial bodies
void CelestialSystem::AddCelestialObject(double mass, double radiusX, double radiusY, 
                                            double velocityX, double velocityY)
{
    CelestialObject currentCelestialObject(mass, radiusX, radiusY, velocityX, velocityY);

    celestialObjects.push_back(currentCelestialObject);
}

// Method to calculate acceleration between the bodies of current interest
double CelestialSystem::AccelerationBetweenBodies(double mass, double distance)
{
    return G*mass/(distance*distance);
}

// Method to calculate the acceleration
void CelestialSystem::TotalAcceleration()
{
    // Get size for loop
    int size = celestialObjects.size();

    // Loop to calculate acceleration for each object
    for (int i = 1; i < size; i++)
    {
        // Current object unpacking
        CelestialObject currentCelestialObject = celestialObjects[i];
        double mass = currentCelestialObject.GetMass();
        double rx = currentCelestialObject.GetRadiusX();
        double ry = currentCelestialObject.GetRadiusY();

        // Variables to hold acceleration
        double accelerationX = 0.0;
        double accelerationY = 0.0;

        // Loop to calculate acceleration for current object
        for (int j = 0; j < size; j++)
        {
            if (i == j) // Can't accelerate itself
            {

            } else 
            {
                // Current object of interest to calculate acceleration from unpacking
                CelestialObject interestedCelestialObject = celestialObjects[j];
                double massI = interestedCelestialObject.GetMass();
                double rxI = interestedCelestialObject.GetRadiusX();
                double ryI = interestedCelestialObject.GetRadiusY();
                
                // Distance between the bodies (sign does not matter as they will get squared)
                double distanceX = rx - rxI;
                double distanceY = ry - ryI;

                // Acceleration calculations
                accelerationX += AccelerationBetweenBodies(massI, distanceX);
                accelerationY += AccelerationBetweenBodies(massI, distanceY);
            }
        }
        currentCelestialObject.SetAccelerationX(accelerationX);
        currentCelestialObject.SetAccelerationY(accelerationY);
    }
}

// Method to calculate the position
void CelestialSystem::VerletMethod(double TimeStep)
{

}
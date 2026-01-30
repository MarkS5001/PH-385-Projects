/*
Class CelestialSystem

Simulates the motion of a multi-body system.

This code has limitations in the form of time step. The objects can come close together,
which means the velocity can become huge. So the velocity can change faster than 
the time step can allow for.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/30/2026
*/

#include "CelestialSystem.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace CS;

// Initialize parameters
CelestialSystem::CelestialSystem(double TimeStep, double Duration, string Filename) : 
                                timeStep(TimeStep), duration(Duration), filename(Filename){};

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
    for (int i = 0; i < size; i++)
    {
        // Current object unpacking
        CelestialObject& currentCelestialObject = celestialObjects[i];
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
                double distanceX = rxI - rx;
                double distanceY = ryI - ry;
                double distanceMag = sqrt(distanceX*distanceX+distanceY*distanceY);

                // Acceleration calculations
                double Acceleration = AccelerationBetweenBodies(massI, distanceMag);
                accelerationX += Acceleration*distanceX/distanceMag;
                accelerationY += Acceleration*distanceY/distanceMag;
            }
        }
        currentCelestialObject.SetAccelerationX(accelerationX);
        currentCelestialObject.SetAccelerationY(accelerationY);
    }
}

// Method to calculate the position
void CelestialSystem::VerletMethod()
{    
    // Get size to loop through all objects
    int size = celestialObjects.size();

    // Initialize file handling
    ofstream Position(filename);

    // Keeps track of condition for loop
    double time = timeStep;

    // Calculate to make the momentum 0
    CelestialSystem::CalculateCenterOfMassCorrection();

    // Save initial positions to the file
    for (int i = 0; i < size; i++)
    {
        CelestialObject& currentCelestialObject = celestialObjects[i];
        Position << currentCelestialObject.GetRadiusX() << "," << currentCelestialObject.GetRadiusY() << "," << 0 << ",";
    }

    // End the line on the file
    Position << time << endl;

    // Calculate initial acceleration
    CelestialSystem::TotalAcceleration();

    // Loop for first Verlet step
    for (int i = 0; i < size; i++)
    {
        // Work one object at a time
        CelestialObject& currentCelestialObject = celestialObjects[i];

        // Unpack needed variables
        double currentX = currentCelestialObject.GetRadiusX();
        double currentY = currentCelestialObject.GetRadiusY();

        double currentVx = currentCelestialObject.GetVelocityX();
        double currentVy = currentCelestialObject.GetVelocityY();

        // unpack acceleration
        double currentAX = currentCelestialObject.GetAccelerationX();
        double currentAY = currentCelestialObject.GetAccelerationY();

        // Update the position
        currentCelestialObject.SetLastRadiusX(currentX);
        currentCelestialObject.SetLastRadiusY(currentY);

        // Uses equation for first Verlet step
        currentCelestialObject.SetRadiusX(currentX+currentVx*timeStep+0.5*currentAX*timeStep*timeStep);
        currentCelestialObject.SetRadiusY(currentY+currentVy*timeStep+0.5*currentAY*timeStep*timeStep);

        // Save new positions
        Position << currentCelestialObject.GetRadiusX() << "," << currentCelestialObject.GetRadiusY() << "," << 0 << ",";
    }

    // Update time
    time += timeStep;

    // End the line on the file
    Position << time << endl;

    // Loop for second Varlet step
    while (time < duration)
    {
        // Calculate acceleration for current loop
        CelestialSystem::TotalAcceleration();

        for (int i = 0; i < size; i++)
        {
            // Work one object at a time
            CelestialObject& currentCelestialObject = celestialObjects[i];

            // Unpack needed variables
            double currentX = currentCelestialObject.GetRadiusX();
            double currentY = currentCelestialObject.GetRadiusY();

            double currentLastX = currentCelestialObject.GetLastRadiusX();
            double currentLastY = currentCelestialObject.GetLastRadiusY();

            // unpack acceleration
            double currentAX = currentCelestialObject.GetAccelerationX();
            double currentAY = currentCelestialObject.GetAccelerationY();

            // Update positions
            currentCelestialObject.SetLastRadiusX(currentX);
            currentCelestialObject.SetLastRadiusY(currentY);

            // Uses equations for subseqent Verlet steps
            currentCelestialObject.SetRadiusX(2*currentX-currentLastX+currentAX*timeStep*timeStep);
            currentCelestialObject.SetRadiusY(2*currentY-currentLastY+currentAY*timeStep*timeStep);
            
            // Save new positions
            Position << currentCelestialObject.GetRadiusX() << "," << currentCelestialObject.GetRadiusY() << "," << 0 << ",";
        }
        // End the line on the file
        Position << time << endl;

        // Update time
        time += timeStep;
    }    
    Position.close();
}

double CelestialSystem::CenterOfMassX()
{
    // Get size for loop
    int size = celestialObjects.size();

    double numerator = 0;
    double totalMass = 0;

    for (int i = 0; i < size; i++)
    {
        // Current object unpacking
        CelestialObject& currentCelestialObject = celestialObjects[i];
        double mass = currentCelestialObject.GetMass();
        double rx = currentCelestialObject.GetRadiusX();

        numerator += mass*rx;
        totalMass += mass;
    }

    return numerator/totalMass;
}

double CelestialSystem::CenterOfMassY()
{
    // Get size for loop
    int size = celestialObjects.size();

    double numerator = 0;
    double totalMass = 0;

    for (int i = 0; i < size; i++)
    {
        // Current object unpacking
        CelestialObject& currentCelestialObject = celestialObjects[i];
        double mass = currentCelestialObject.GetMass();
        double rx = currentCelestialObject.GetRadiusY();

        numerator += mass*rx;
        totalMass += mass;
    }

    return numerator/totalMass;
}

double CelestialSystem::VelocityOfCenterOfMassX()
{
    // Get size for loop
    int size = celestialObjects.size();

    double numerator = 0;
    double totalMass = 0;

    for (int i = 0; i < size; i++)
    {
        // Current object unpacking
        CelestialObject& currentCelestialObject = celestialObjects[i];
        double mass = currentCelestialObject.GetMass();
        double vx = currentCelestialObject.GetVelocityX();

        numerator += mass*vx;
        totalMass += mass;
    }

    return numerator/totalMass;
}

double CelestialSystem::VelocityOfCenterOfMassY()
{
    // Get size for loop
    int size = celestialObjects.size();

    double numerator = 0;
    double totalMass = 0;

    for (int i = 0; i < size; i++)
    {
        // Current object unpacking
        CelestialObject& currentCelestialObject = celestialObjects[i];
        double mass = currentCelestialObject.GetMass();
        double vx = currentCelestialObject.GetVelocityY();

        numerator += mass*vx;
        totalMass += mass;
    }

    return numerator/totalMass;
}

void CelestialSystem::CalculateCenterOfMassCorrection()
{
    // Size to loop over
    double size = celestialObjects.size();

    // Unpack needed variables
    double crx = CelestialSystem::CenterOfMassX();
    double cry = CelestialSystem::CenterOfMassY();
    double cvx = CelestialSystem::VelocityOfCenterOfMassX();
    double cvy = CelestialSystem::VelocityOfCenterOfMassY();

    for (int i = 0; i < size; i++)
    {
        CelestialObject& currentCelestialObject = celestialObjects[i];
        double rx = currentCelestialObject.GetRadiusX();
        double ry = currentCelestialObject.GetRadiusY();
        double vx = currentCelestialObject.GetVelocityX();
        double vy = currentCelestialObject.GetVelocityY();

        currentCelestialObject.SetRadiusX(rx-crx);
        currentCelestialObject.SetRadiusY(ry-cry);
        currentCelestialObject.SetVelocityX(vx-cvx);
        currentCelestialObject.SetVelocityY(vy-cvy);
    }    
}
/*
Class CelestialObject

Holds the data of the celestial object.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/26/2026
*/

#include "CelestialObject.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace CO;

// Constructor for the celestial object
CelestialObject::CelestialObject(const double Mass, const double RadiusX, const double RadiusY, 
                                    const double VelocityX, const double VelocityY) : mass(Mass)
{
    radius[0] = RadiusX;
    radius[1] = RadiusY;
    velocity[0] = VelocityX;
    velocity[1] = VelocityY;
};

// The following nine methods set the parameters the celestial object can hold
void CelestialObject::SetMass(double Mass)
{
    mass = Mass;
};

void CelestialObject::SetRadiusX(double RadiusX)
{
    radius[0] = RadiusX;
};

void CelestialObject::SetRadiusY(double RadiusY)
{
    radius[2] = RadiusY;
};

void CelestialObject::SetLastRadiusX(double RadiusX)
{
    lastRadius[0] = RadiusX;
};

void CelestialObject::SetLastRadiusY(double RadiusY)
{
    lastRadius[2] = RadiusY;
};

void CelestialObject::SetVelocityX(double VelocityX)
{
    velocity[0] = VelocityX;
};

void CelestialObject::SetVelocityY(double VelocityY)
{
    velocity[1] = VelocityY;
};

void CelestialObject::SetAccelerationX(double AccelerationX)
{
    acceleration[0] = AccelerationX;
};

void CelestialObject::SetAccelerationY(double AccelerationY)
{
    acceleration[1] = AccelerationY;
};

// The following nine methods get the parameters the celestial object can hold
double CelestialObject::GetMass()
{
    return mass;
};

double CelestialObject::GetRadiusX()
{
    return radius[0];
};

double CelestialObject::GetRadiusY()
{
    return radius[1];
};

double CelestialObject::GetLastRadiusX()
{
    return lastRadius[0];
};

double CelestialObject::GetLastRadiusY()
{
    return lastRadius[1];
};

double CelestialObject::GetVelocityX()
{
    return velocity[0];
};

double CelestialObject::GetVelocityY()
{
    return velocity[1];
};

double CelestialObject::GetAccelerationX()
{
    return acceleration[0];
};

double CelestialObject::GetAccelerationY()
{
    return acceleration[1];
};
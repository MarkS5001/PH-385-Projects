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
CelestialObject::CelestialObject(const double Mass, const double Radius, const double Velocity) : 
                                    mass(Mass), radius(Radius), velocity(Velocity){};

// The following three methods set the parameters the celestial object can hold
void CelestialObject::SetMass(double Mass)
{
    mass = Mass;
};

void CelestialObject::SetRadius(double Radius)
{
    radius = Radius;
};

void CelestialObject::SetVelocity(double Velocity)
{
    velocity = Velocity;
};

// The following three methods get the parameters the celestial object can hold
double CelestialObject::GetMass()
{
    return mass;
};

double CelestialObject::GetRadius()
{
    return radius;
};

double CelestialObject::GetVelocity()
{
    return velocity;
};
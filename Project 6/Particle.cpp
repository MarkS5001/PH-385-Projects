/*
Class Particle

Holds the position of the particle

Author: Mark Smith (smi20046@byui.edu)
Date: 2/17/2026
*/

#include "Particle.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace P;

Particle::Particle(double X, double Y, double Z) : x(X), y(Y), z(Z) {}

void Particle::Setx(double X)
{
    x = X;
}

void Particle::Sety(double Y)
{
    y = Y;
}

void Particle::Setz(double Z)
{
    z = Z;
}
double Particle::Getx()
{
    return x;
}

double Particle::Gety()
{
    return y;
}

double Particle::Getz()
{
    return z;
}
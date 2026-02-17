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

Particle::Particle(double R, double Phi) : r(R), phi(Phi) {}

void Particle::Setr(double R)
{
    r = R;
}
void Particle::Setphi(double Phi)
{
    phi = Phi;
}
double Particle::Getr()
{
    return r;
}

double Particle::Getphi()
{
    return phi;
}
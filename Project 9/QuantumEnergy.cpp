/*
Class QuantumEnergy

Calculates the energy levels for quantum wells.

This code has limitations in the form of space step.

Author: Mark Smith (smi20046@byui.edu)
Date: 3/16/2026
*/

#include "QuantumEnergy.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace QE;

QuantumEnergy::QuantumEnergy(double WellSize, double Dx, double DE, double NExcited, std::string Filename) :
                                wellSize(WellSize), dx(Dx), dE(DE), nExcited(NExcited), filename(Filename),
                                psi(WellSize/Dx*NExcited), positions(WellSize/Dx){};

double QuantumEnergy::Potential(int n, double x)
{
    return pow(x,n)/n;
}

void QuantumEnergy::Normalize()
{
    for (int n = 1; n <= nExcited; n++)
    {
        
    }
}

void QuantumEnergy::Shooting() // Starts at middle and goes to inf, then the other side is a reflection
{

}

void QuantumEnergy::Matching() // Starts at inf and goes to the middle, then the other side is a reflection
{

}
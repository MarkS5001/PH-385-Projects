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
                                psi((WellSize/Dx)*3*NExcited), positions(WellSize/Dx), energies(nExcited,0.0){};

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

void QuantumEnergy::Shooting(int N) // Starts at middle and goes to inf, then the other side is a reflection
{
    int width = wellSize/dx*3;
    int middle = width/2;

    for (int n = 0; n < nExcited; n++)
    {
        double difference = 1e9;
        int offset = n*width;

        for (double energy = energies[n]; energy < 20.0; energy += dE)
        {
            // Even parity
            psi[offset+middle] = 1;
            psi[offset+middle-1] = 1;

            for (int i = 1; i < middle-1; i++)
            {
                // Unpack needed values
                double lastPsi = psi[offset+middle+i-1];
                double currentPsi = psi[offset+middle+i];
                double x = (middle+i)*dx;

                // Calculate new value
                double newPsi = Schrodinger(lastPsi, currentPsi, energy, N, x);

                // Set new value
                psi[offset+middle+i+1] = newPsi;
                psi[offset+middle-i-2] = newPsi;
            }

            if (abs(psi[offset+width-1]) < difference)
            {
                difference = abs(psi[offset+width-1]);
                energies[n] = energy;
            }
        }
    }
}

void QuantumEnergy::Matching(int N) // Starts at inf and goes to the middle, then the other side is a reflection
{

}

double QuantumEnergy::Schrodinger(double last, double current, double energy, int n, double x)
{
    return (-2*dx*dx*((energy-Potential(n, x))*current))+2*current-last;
}
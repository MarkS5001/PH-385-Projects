/*
PH 385 Project 8 Main File

Models the motion of molecules

The user inputs the mass of the ball, diameter of the ball, air density, drag
coefficient, initial position, initial velocity, spin angular velocity,
and time step, all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 3/2/2026
*/
#include <iostream>
#include <ctime>
#include "MolecularDynamics.hpp"

using namespace std;
using namespace MD;

int gridSize = 20;
int numParticles = 30;
double deltaEnergy = 0.01;
int steps = 80000;
double cutoffLength = 17.0;
double timeStep = 1e-2;
string filename = "resultsP8.txt";

int main()
{
    clock_t start = clock(); // Get program start time

    MolecularDynamics simulation(gridSize, numParticles, deltaEnergy, steps, cutoffLength, timeStep, filename);

    int particlesPlaced = 0;
    for (double iy = 1.0; iy < gridSize && particlesPlaced < numParticles; iy += 1.5) 
    {
        for (double ix = 1.0; ix < gridSize && particlesPlaced < numParticles; ix += 1.5) 
        {
            simulation.GivePositions(particlesPlaced, ix, iy);
            particlesPlaced++;
        }
    }

    simulation.Dynamics();

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
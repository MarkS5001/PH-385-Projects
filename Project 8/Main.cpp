/*
PH 385 Project 8 Main File

Models the motion of molecules

The user inputs the grid size, number of particles, energy change
per step, number of steps, a cutoff length,
and time step. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 3/12/2026
*/
#include <iostream>
#include <ctime>
#include "MolecularDynamics.hpp"

using namespace std;
using namespace MD;

int gridSize = 20;
int numParticles = 25;
double deltaEnergy = 1e-4;
int steps = 290000;
double cutoffLength = 7.0;
double timeStep = 1e-3;
string filenameup = "resultsP8_up.txt";
string filenamedowwn = "resultsP8_down.txt";

int main()
{
    clock_t start = clock(); // Get program start time

    MolecularDynamics simulation(gridSize, numParticles, deltaEnergy, steps, cutoffLength, timeStep, filenameup, filenamedown);

    int particlesPlaced = 0;
    for (double iy = 5.0; iy < gridSize/2 && particlesPlaced < numParticles; iy += 1.2) 
    {
        for (double ix = 5.0; ix < gridSize/2 && particlesPlaced < numParticles; ix += 1.2) 
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
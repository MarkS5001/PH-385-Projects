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
#include "MolecularDynamics.cpp"

using namespace std;
using namespace MD;

int gridSize = 20;
int numParticles = 1;
double deltaEnergy = 0.01;
int steps = 200;
double cutoffLength = 7;
double timeStep = 0.01;
string filename = "resultsP8.txt";

int main()
{
    clock_t start = clock(); // Get program start time

    MolecularDynamics simulation(gridSize, numParticles, deltaEnergy, steps, cutoffLength, timeStep, filename);

    int x = 0.1;
    int y = 0.1;
    for (int i = 0; i < numParticles; i++)
    {
        simulation.GivePositions(i, x, y);
        
        if (x < gridSize)
        {
            x++;
        }
        else
        {
            x = 0.1;

            if (y < gridSize)
            {
                y++;
            }
            else
            {
                y = 0.1;
            }
        }
    }

    simulation.Dynamics();

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
/*
PH 385 Project 6 Main File

Models the motion of solute in a solvent.

The user inputs the boundary positions, positions of particles,
duration of simulation, all in arbitrary units. This is followed 
by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/17/2026
*/
#include <iostream>
#include <ctime>
#include "Diffusion.cpp"
#include "Particle.cpp"

using namespace std;

string filename = "resultsP6.txt";
double boundary = 0.5;
int duration = 1000;
double rstep = 0.025;
int numberParticles = 10;

int main()
{
    clock_t start = clock(); // Get program start time

    // Give initial parameters
    Diffusion diffusion(boundary, duration, rstep, filename);
    
    // Add particles
    for (int i = 0; i < numberParticles; i++)
    {
        diffusion.AddParticle(0,0,0);
    }

    // Start diffusion
    diffusion.Diffuse();

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
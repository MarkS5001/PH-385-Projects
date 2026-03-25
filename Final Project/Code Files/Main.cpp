/*
PH 385 Final Project Main File

Fluid mechanics simulation using smoothed particle hydrodynamics.

The user inputs . This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 3/23/2026
*/
#include <iostream>
#include <ctime>
#include "SPH.hpp"

using namespace std;

int main()
{
    clock_t start = clock(); // Get program start time

    // Initial parameters for simulation
    double h = 0.45; // Smoothing length
    double dt = 0.002;
    string filename = "resultsFP.txt";
    double width = 5.0;
    double height = 5.0;
    double depth = 5.0;

    // Starting position to put particles in
    double x = 0.001;
    double y = 0.001;
    double z = 0.001;

    // Particles to put in each starting direction
    int nx = 6;
    int ny = 6;
    int nz = 6;

    // Total number of particles based off above
    int numParticles = nx*ny*nz;


    FM::SPH fluidSystem(numParticles, h, dt, filename, width, height, depth);
    
    fluidSystem.initVolume(x, y, z, nx, ny, nz);

    fluidSystem.simulation(500);

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
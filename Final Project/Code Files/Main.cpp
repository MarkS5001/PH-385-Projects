/*
PH 385 Final Project Main File

Fluid mechanics simulation using smoothed particle hydrodynamics.

The user inputs smoothing length, step size, starting point for 
particles, how many particles in each direction, and box dimensions, 
all in arbitrary units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 4/1/2026
*/
#include <iostream>
#include <ctime>
#include "SPH.hpp"

using namespace std;

int main()
{
    clock_t start = clock(); // Get program start time

    // Initial parameters for simulation
    double h = 0.3;//1;//0.45; // Smoothing length
    double dt = 0.001;
    string filename = "resultsFP.txt";
    double width = 5.0;
    double height = 50.0;
    double depth = 5.0;

    // Starting position to put particles in
    double x = 2.001;
    double y = 2.001;
    double z = 2.001;

    // Particles to put in each starting direction
    int nx = 7;
    int ny = 70;
    int nz = 7;

    // Total number of particles based off above
    int numParticles = nx*ny*nz;


    FM::SPH fluidSystem(numParticles, h, dt, filename, width, height, depth);
    
    fluidSystem.initVolume(x, y, z, nx, ny, nz);

    fluidSystem.simulation(5000);

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
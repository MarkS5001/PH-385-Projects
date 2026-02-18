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

double boundary = 0.5;
int duration = 1000;
int numberParticles = 2500;//10;

string filename025 = "resultsP6_025.txt";
double rstep025 = 0.025;

string filename01 = "resultsP6_01.txt";
double rstep01 = 0.01;

string filename02 = "resultsP6_02.txt";
double rstep02 = 0.02;

string filename03 = "resultsP6_03.txt";
double rstep03 = 0.03;

string filename04 = "resultsP6_04.txt";
double rstep04 = 0.04;


int main()
{
    clock_t start = clock(); // Get program start time

    // Give initial parameters
    Diffusion diffusion025(boundary, duration, rstep025, filename025);
    Diffusion diffusion01(boundary, duration, rstep01, filename01);
    Diffusion diffusion02(boundary, duration, rstep02, filename02);
    Diffusion diffusion03(boundary, duration, rstep03, filename03);
    Diffusion diffusion04(boundary, duration, rstep04, filename04);
    
    // Add particles
    for (int i = 0; i < numberParticles; i++)
    {
        diffusion025.AddParticle(0,0,0);
        diffusion01.AddParticle(0,0,0);
        diffusion02.AddParticle(0,0,0);
        diffusion03.AddParticle(0,0,0);
        diffusion04.AddParticle(0,0,0);
    }

    // Start diffusion
    diffusion025.Diffuse();
    diffusion01.Diffuse();
    diffusion02.Diffuse();
    diffusion03.Diffuse();
    diffusion04.Diffuse();

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
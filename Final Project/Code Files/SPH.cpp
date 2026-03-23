/*
Class SPH

Fluid mechanics simulation using smoothed particle hydrodynamics.

This code has limitations .

Author: Mark Smith (smi20046@byui.edu)
Date: 3/23/2026
*/

#include "SPH.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace FM;

SPH::SPH(int NumParticles, double H, double Dt, std::string Filename, double Width, double Height, double Depth) :
            numParticles(NumParticles), h(H), h2(H*H), dt(Dt), filename(Filename),
            width(Width), height(Height), depth(Depth), gridX(ceil(Width/H)), gridY(ceil(Height/H)), 
            gridZ(ceil(Depth/H)), pos(NumParticles*3, 0.0), vel(NumParticles*3, 0.0), 
            acc(NumParticles*3, 0.0), rho(NumParticles, 0.0), p(NumParticles, 0.0), 
            head(ceil(Width/H) * ceil(Height/H) * ceil(Depth/H), -1), next(NumParticles, -1), 
            termPoly(315/(64*M_PI*pow(H,9))), termSpiky(15/(M_PI*pow(H,6))), termVis(15/(2*M_PI*pow(H,3))) {}

void SPH::initVolume(double x, double y, double z, int nx, int ny, int nz)
{
    int particle = 0;
    double spacing = h*0.8;

    for (int X = 0; X < nx; X++)
    {
        for (int Y = 0; Y < ny; Y++)
        {
            for (int Z = 0; Z < nz; Z++)
            {
                pos[particle*3+0] = x+X*spacing; // Initial x position
                pos[particle*3+1] = y+Y*spacing; // Initial y position
                pos[particle*3+2] = z+Z*spacing; // Initial z position

                particle++;

                if (particle >= numParticles) // Stop if number of particles is reached
                {
                    return;
                }
            }
        }
    }
}

void SPH::simulation(int duration)
{

}

void SPH::buildGrid() // Sub cubes in volume to smooth over
{
    std::fill(head.begin(), head.end(), -1); // reset head vector to empty

    for (int i = 0; i < numParticles; i++)
    {
        // Get which grid it's in
        int ix = floor(pos[i*3+0]/h);
        int iy = floor(pos[i*3+1]/h);
        int iz = floor(pos[i*3+2]/h);

        // Make sure it's in a grid
        ix = std::max(0, std::min(ix, gridX - 1));
        iy = std::max(0, std::min(iy, gridY - 1));
        iz = std::max(0, std::min(iz, gridZ - 1));

        int subCube = getGridIdx(ix,iy,iz);
        next[i] = head[subCube];
        head[subCube] = i;
    }
}

void SPH::computeDensityPressure()
{

}

void SPH::computeForces()
{

}

void SPH::integrate()
{

}

void SPH::checkCollisions()
{

}


// Kernels
double SPH::W_poly6(double r2)
{
    if (r2 < h2)
    {
        double r = h2-r2;
        return termPoly*r*r*r;
    }
    else
    {
        return 0;
    }
}

double SPH::W_spiky_grad(double r)
{
    if (0 <= r && r <= h)
    {
        double d = h-r;
        return -termSpiky*d*d;
    }
    else
    {
        return 0;
    }
}

double SPH::W_visc_laplacian(double r)
{
    if (0 <= r && r <= h)
    {
        return termVis*(h-r);//(-r*r*r/(2*h2*h)+r*r/h2+h/(2*r)-1);
    }
    else
    {
        return 0;
    }
}

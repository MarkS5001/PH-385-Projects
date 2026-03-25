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
            termPoly(315/(64*M_PI*pow(H,9))), termSpiky(30/(M_PI*pow(H,6))), termVis(45/(M_PI*pow(H,6))) {}

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
    // Set up file handling and save initial positions
    ofstream Positions(filename);
    for (int i = 0; i < numParticles; i++)
    {
        Positions << pos[i*3+0] << " " << pos[i*3+1] << " " << pos[i*3+2] << endl;
    }
    Positions << endl << endl;

    for (int t = 0; t < duration; t++)
    {
        // Set up grid
        buildGrid();

        // Get properties
        computeDensityPressure();
        computeForces();

        // Move particles
        integrate();

        // Save positions
        for (int i = 0; i < numParticles; i++)
        {
            Positions << pos[i*3+0] << " " << pos[i*3+1] << " " << pos[i*3+2] << endl;
        }
        Positions << endl << endl;
    }
    Positions.close();
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
    for (int i = 0; i < numParticles; i++) 
    {
        rho[i] = 0.0; // Default density

        // Find which cell particle 'i' is in
        int ix = floor(pos[i*3+0]/h);
        int iy = floor(pos[i*3+1]/h);
        int iz = floor(pos[i*3+2]/h);

        // Look at the cells surrounding particle
        for (int ni = ix - 1; ni <= ix + 1; ni++) 
        {
            for (int nj = iy - 1; nj <= iy + 1; nj++) 
            {
                for (int nk = iz - 1; nk <= iz + 1; nk++) 
                {    
                    // Safety: Skip if the neighbor cell is outside the world
                    if (ni < 0 || ni >= gridX || nj < 0 || nj >= gridY || nk < 0 || nk >= gridZ) continue;

                    int targetCell = getGridIdx(ni, nj, nk);
                    int j = head[targetCell]; // Get the first particle in this cell

                    // Go through linked list in this cell
                    while (j != -1) 
                    {
                        // Calculate distance squared (r^2)
                        double dx = pos[i*3+0] - pos[j*3+0];
                        double dy = pos[i*3+1] - pos[j*3+1];
                        double dz = pos[i*3+2] - pos[j*3+2];
                        double r2 = dx*dx + dy*dy + dz*dz;

                        if (r2 < h2) 
                        {
                            // Muller Density Equation: rho = sum(m * W)
                            rho[i] += m * W_poly6(r2);
                        }
                        
                        j = next[j]; // Move to the next particle in the "mailbox"
                    }
                }
            }
        }

        // Calculate pressure
        p[i] = stiff * (rho[i] - rho_0);
        if (p[i] < 0) p[i] = 0; // Clamp pressure to prevent clumping
    }
}

void SPH::computeForces()
{
    for (int i = 0; i < numParticles; i++) 
    {
        acc[i*3+0] = 0.0; // Default density
        acc[i*3+1] = 0.0;
        acc[i*3+2] = 0.0;

        // Find which cell particle 'i' is in
        int ix = floor(pos[i*3+0]/h);
        int iy = floor(pos[i*3+1]/h);
        int iz = floor(pos[i*3+2]/h);

        // Look at the cells surrounding particle
        for (int ni = ix - 1; ni <= ix + 1; ni++) 
        {
            for (int nj = iy - 1; nj <= iy + 1; nj++) 
            {
                for (int nk = iz - 1; nk <= iz + 1; nk++) 
                {    
                    // Safety: Skip if the neighbor cell is outside the world
                    if (ni < 0 || ni >= gridX || nj < 0 || nj >= gridY || nk < 0 || nk >= gridZ) continue;

                    int targetCell = getGridIdx(ni, nj, nk);
                    int j = head[targetCell]; // Get the first particle in this cell

                    // Go through linked list in this cell
                    while (j != -1) 
                    {
                        if (i != j)
                        {
                            // Calculate distance squared (r^2)
                            double dx = pos[i*3+0] - pos[j*3+0];
                            double dy = pos[i*3+1] - pos[j*3+1];
                            double dz = pos[i*3+2] - pos[j*3+2];
                            double r2 = dx*dx + dy*dy + dz*dz;

                            if (r2 < h2 && r2 > 1e-6) 
                            {
                                double r = sqrt(r2);

                                // Acceleration from pressure
                                double ap = -m*(p[i]+p[j])/(2*rho[j])*W_spiky_grad(r);

                                // Acceleration from viscosity
                                double avx = visc*m*(vel[j*3+0]-vel[i*3+0])/rho[j]*W_visc_laplacian(r);
                                double avy = visc*m*(vel[j*3+1]-vel[i*3+1])/rho[j]*W_visc_laplacian(r);
                                double avz = visc*m*(vel[j*3+2]-vel[i*3+2])/rho[j]*W_visc_laplacian(r);

                                // Assign acceleration
                                acc[i*3+0] += ap*dx/r+avx;
                                acc[i*3+1] += ap*dy/r+avy;
                                acc[i*3+2] += ap*dz/r+avz;

                            }
                        }
                        j = next[j]; // Move to the next particle in the "mailbox"
                    }
                }
            }
        }
        // Add gravity
        acc[i*3+1] += g;
    }
}

void SPH::integrate()
{
    for (int i = 0; i < numParticles; i++)
    {
        // Update velocity
        vel[i*3+0] += acc[i*3+0]*dt;
        vel[i*3+1] += acc[i*3+1]*dt;
        vel[i*3+2] += acc[i*3+2]*dt;

        // Update position
        pos[i*3+0] += vel[i*3+0]*dt;
        pos[i*3+1] += vel[i*3+1]*dt;
        pos[i*3+2] += vel[i*3+2]*dt;

        // Boundary conditions
        if (pos[i*3+0] < 0.0) 
        {
            pos[i*3+0] = 0.001; // Stick it to the wall
            vel[i*3+0] *= -0.5; // Have it loose energy
        }
        if (pos[i*3+0] > width)
        {
            pos[i*3+0] = width-0.001; // Stick it to the wall
            vel[i*3+0] *= -0.5; // Have it loose energy
        }

        if (pos[i*3+1] < 0.0) 
        {
            pos[i*3+1] = 0.001; // Stick it to the wall
            vel[i*3+1] *= -0.5; // Have it loose energy
        }
        if (pos[i*3+1] > height)
        {
            pos[i*3+1] = height-0.001; // Stick it to the wall
            vel[i*3+1] *= -0.5; // Have it loose energy
        }

        if (pos[i*3+2] < 0.0) 
        {
            pos[i*3+2] = 0.001; // Stick it to the wall
            vel[i*3+2] *= -0.5; // Have it loose energy
        }
        if (pos[i*3+2] > depth)
        {
            pos[i*3+2] = depth-0.001; // Stick it to the wall
            vel[i*3+2] *= -0.5; // Have it loose energy
        }

    }
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
        return termVis*(h-r);
    }
    else
    {
        return 0;
    }
}

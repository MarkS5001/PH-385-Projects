/*
Header file for SPH class

Creates an outline of what the SPH class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 3/27/2026
*/

#pragma once
#include <vector>
#include <string>

namespace FM
{
    class SPH
    {
        private:
            int numParticles; // Number of particles in the box
            double dt; // Time step of simulation
            std::string filename; // File to save to
            double width; // x dimension of the box
            double height; // y dimension of the box
            double depth; // z dimension of the box

            const double rho_0 = 3.0;//5.0//0; //1000.0; // Rest density of water
            const double visc = 5.5; // Viscosity (adjust for "thickness")
            const double stiff = 2000;//5000000.0;//200.0; // Bulk Modulus (Tait Equation 'B')
            const double m = 0.02; // Mass per particle
            const double g = -9.81; // Gravity acceleration
            const double h; // Smoothing length
            const double h2; // h^2
            const double termPoly; // coefficient for poly kernel
            const double termSpiky; // coefficient for spiky kernel
            const double termVis; // coefficient fot vis kernel

            std::vector<double> pos; // Size: n * 3 [x0, y0, z0, x1, y1...]
            std::vector<double> vel; // Size: n * 3 [vx0, vy0, vz0...]
            std::vector<double> acc; // Size: n * 3 [ax0, ay0, az0...]
            std::vector<double> rho; // Size: n (Density)
            std::vector<double> p; // Size: n (Pressure)

            int gridX, gridY, gridZ; // Grid size of the cubes within the volume
            std::vector<int> head; // "Filing cabinet" for cells
            std::vector<int> next; // "Notes in pockets" for particles

        public:
            SPH(int NumParticles, double H, double Dt, std::string Filename, double Width, double Height, double Depth); // Constructor to set initial values
            void initVolume(double x, double y, double z, int nx, int ny, int nz); // Puts all particles in volume
            void simulation(int duration); // Simulation method

            void buildGrid(); // Rebuilds linked-list every frame
            void computeDensityPressure(); // Pass 1: Density -> Tait Eq -> Pressure
            void computeForces(); // Pass 2: Pressure + Viscosity + Gravity
            void integrate(); // Moves particles
            void checkCollisions(); // Keeps particles inside the box

            // Kernels for fluid proprieties
            double W_poly6(double r2);
            double W_spiky_grad(double r);
            double W_visc_laplacian(double r);

            // Gets index for particle
            inline int getGridIdx(int ix, int iy, int iz) const {
                return ix * (gridY * gridZ) + iy * gridZ + iz;
            }
    };
}
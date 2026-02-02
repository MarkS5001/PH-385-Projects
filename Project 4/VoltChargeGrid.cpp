/*
Class VoltChargeGrid

Solves for the voltage of the grids

This code has limitations in the form of time step. With the use of Euler's
method, h (the time step) squared terms are neglected, and these terms will add up.
You can also decrease the time step to decrease the error, however the number
of steps needed will increase if a user does this.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/2/2026
*/

#include "VoltChargeGrid.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace VCG;

// Give initial parameters
VoltChargeGrid::VoltChargeGrid(/*const double GridSize, */const double GridSpacing) : gridSpacing(GridSpacing)
{};

// Add point charge to grid
void VoltChargeGrid::AddCharge(double q, double rx, double ry, double rz)
{
    // Change origin from problem to code
    double ix = ChangeIndex(rx);
    double iy = ChangeIndex(ry);
    double iz = ChangeIndex(rz);

    // Calculate voltage from charge
    double v =VoltageFromPointCharge(q, gridSpacing);

    // Place voltage from charge to adjoining grid points
    grid[iz+1][iy][ix] = v;
    grid[iz-1][iy][ix] = v;
    grid[iz][iy+1][ix] = v;
    grid[iz][iy-1][ix] = v;
    grid[iz][iy][ix+1] = v;
    grid[iz][iy][ix-1] = v;
}

// Add surface of voltage to grid
void VoltChargeGrid::AddVoltageCircle(double V, double rx, double ry, double rz, double radius, bool D2 = true)
{
    if (D2)
    {
        // Change origin from problem to code
        double ix = ChangeIndex(rx);
        double iy = ChangeIndex(ry);

        for (int y = 0; y <= gridSize; y++)
        {
            for (int x = 0; x <= gridSize; x++)
            {
                if (sqrt((y-iy)*(y-iy)+(x-ix)*(x-ix))*gridSpacing <= radius)
                {
                    grid[0][y][x] = V;
                }
            }
        }
    } 
    else
    {
        // Change origin from problem to code
        double ix = ChangeIndex(rx);
        double iy = ChangeIndex(ry);
        double iz = ChangeIndex(rz);
        
        for (int z = 0; z <=gridSize; z++)
        {
            for (int y = 0; y <= gridSize; y++)
            {
                for (int x = 0; x <= gridSize; x++)
                {
                    if (sqrt((z-iz)*(z-iz)+(y-iy)*(y-iy)+(x-ix)*(x-ix))*gridSpacing <= radius)
                    {
                        grid[z][y][x] = V;
                    }
                }
            }
        }
    }
}

// Calculate voltage from point charge
double VoltChargeGrid::VoltageFromPointCharge(double q, double r)
{
    return k*q/r;
}

// Finds the index value from having the origin in the center of the cube
double VoltChargeGrid::ChangeIndex(double r)
{
    return (r+offset)/gridSpacing;
}

// Method to calculate the voltage from the grid
void VoltChargeGrid::Relaxation()
{

}
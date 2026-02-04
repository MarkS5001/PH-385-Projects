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
VoltChargeGrid::VoltChargeGrid(int NumberOfIterations, bool DD3, std::string Filename) : 
                                numberOfIterations(NumberOfIterations), D3(DD3), filename(Filename)
{};

// Add point charge to list
void VoltChargeGrid::AddPointCharge(double q, double rx, double ry, double rz)
{
    pointCharges.push_back({q, rx, ry, rz});
}

// Add point charge to grid
void VoltChargeGrid::AddChargeGrid()
{
    for (const auto& charge : pointCharges)
    {
        // Unpack the charge
        double q = charge[0];
        double rx = charge[1];
        double ry = charge[2];
        double rz = charge[3];

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
}

// Add circle of surface charge to list
void VoltChargeGrid::AddVoltageCircle(double V, double rx, double ry, double rz, double radius, double D2)
{
    voltageCircle.push_back({V, rx, ry, rz, radius, D2});
}

// Add surface of voltage to grid
void VoltChargeGrid::AddVoltageCircleGrid()
{
    for (const auto& voltCirlce : voltageCircle)
    {
        // Unpack the circle
        double V = voltCirlce[0];
        double rx = voltCirlce[1];
        double ry = voltCirlce[2];
        double rz = voltCirlce[3];
        double radius = voltCirlce[4];
        double D2 = voltCirlce[5];

        if (D2 > 0)
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

            for (int z = 0; z <= gridSize; z++)
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
    for (int i = 0; i < numberOfIterations; i++)
    {
        if (D3)
        {
            for (int z = 1; z < gridSize; z++)
            {
                for (int y = 1; y < gridSize; y++)
                {
                    for (int x = 1; x < gridSize; x++)
                    {
                        grid[z][y][x] = 1/6*(grid[z][y][x-1]+grid[z][y][x+1]+grid[z][y-1][x]+grid[z][y+1][x]+grid[z-1][y][x]+grid[z+1][y][x]);
                    }
                }
                
                // Keep point charges and surface voltages
                VoltChargeGrid::AddChargeGrid();
                VoltChargeGrid::AddVoltageCircleGrid();
            }
        }
        else
        {
            for (int y = 1; y < gridSize; y++)
            {
                for (int x = 1; x < gridSize; x++)
                {
                    grid[0][y][x] = 1/4*(grid[0][y][x-1]+grid[0][y][x+1]+grid[0][y-1][x]+grid[0][y+1][x]);
                }
                
                // Keep point charges and surface voltages
                VoltChargeGrid::AddChargeGrid();
                VoltChargeGrid::AddVoltageCircleGrid();
            }
        }
    }
}

void VoltChargeGrid::SaveResults()
{
    // Initialize file handling
    ofstream voltage(filename);

    for (int i = 0; i < gridSize; ++i) 
    {
        for (int j = 0; j < gridSize; ++j) 
        {
            for (int k = 0; k < gridSize; ++k) 
            {
                // Write: x y z value
                voltage << i << " " << j << " " << k << " " << grid[i][j][k] << "\n";
            }
            
            // One blank line after each "row" in a slice
            voltage << "\n";
        }
        
        // Two blank lines after each 2D "slice"
        voltage << "\n\n";
    }

    voltage.close();
}
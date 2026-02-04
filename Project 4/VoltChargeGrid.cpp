/*
Class VoltChargeGrid

Solves for the voltage of the grids

This code has limitations in the form of time step. With the use of Euler's
method, h (the time step) squared terms are neglected, and these terms will add up.
You can also decrease the time step to decrease the error, however the number
of steps needed will increase if a user does this.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/3/2026
*/

#include "VoltChargeGrid.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace VCG;

// Give initial parameters
VoltChargeGrid::VoltChargeGrid(int NumberOfIterations, bool DD3, std::string Filename, int GridSize) : 
                                numberOfIterations(NumberOfIterations), D3(DD3), filename(Filename), 
                                grid(GridSize*GridSize*GridSize, 0.0)
{};

// Add point charge to list
void VoltChargeGrid::AddPointCharge(double q, int rx, int ry, int rz)
{
    pointCharges.push_back({rx, ry, rz});
    pointChargesCharge.push_back(q);
}

// Add point charge to grid
void VoltChargeGrid::AddChargeGrid()
{
    for (int i = 0; i < pointCharges.size(); i++)
    {
        array<int, 3> charge = pointCharges[i];

        // Unpack the charge
        int x = charge[0];
        int y = charge[1];
        int z = charge[2];

        // Get charge
        double q = pointChargesCharge[i];

        // Change origin from problem to code for the six spaces surrounding point charge
        int ir1 = ChangeIndex(x+1,y,z);
        int ir2 = ChangeIndex(x-1,y,z);
        int ir3 = ChangeIndex(x,y+1,z);
        int ir4 = ChangeIndex(x,y-1,z);
        int ir5 = ChangeIndex(x,y,z+1);
        int ir6 = ChangeIndex(x,y,z-1);

        // Calculate voltage from charge
        double v = VoltageFromPointCharge(q, gridSpacing);

        // Place voltage from charge to adjoining grid points
        grid[ir1] = v;
        grid[ir2] = v;
        grid[ir3] = v;
        grid[ir4] = v;
        grid[ir5] = v;
        grid[ir6] = v;
    }
}

// Add circle of surface charge to list
void VoltChargeGrid::AddVoltageCircle(double V, int rx, int ry, int rz, int radius, int D2)
{
    voltageCircles.push_back({rx, ry, rz, radius, D2});
    voltageCirclesVoltage.push_back({V});
}

// Add surface of voltage to grid
void VoltChargeGrid::AddVoltageCircleGrid()
{
    for (int i = 0; i < voltageCircles.size(); i++)
    {
        array<int, 5> voltCircle = voltageCircles[i];

        // Unpack the circle
        int rx = voltCircle[0];
        int ry = voltCircle[1];
        int rz = voltCircle[2];
        int radius = voltCircle[3];
        int D2 = voltCircle[4];

        // Get voltage of the circle
        double V = voltageCirclesVoltage[i];

        if (D2 != 0)
        {
            // Change origin from problem to code
            int ir = ChangeIndex(rx, ry, 0);

            for (int y = 0; y <= gridSize; y++)
            {
                for (int x = 0; x <= gridSize; x++)
                {
                    if (sqrt((y-ry)*(y-ry)+(x-rx)*(x-rx))*gridSpacing <= radius)
                    {
                        int icr = ChangeIndex(x, y, 0); // Get index for current point
                        grid[icr] = V;
                    }
                }
            }
        } 
        else
        {
            // Change origin from problem to code
            int ir = ChangeIndex(rx, ry, rz);

            for (int z = 0; z <= gridSize; z++)
            {
                for (int y = 0; y <= gridSize; y++)
                {
                    for (int x = 0; x <= gridSize; x++)
                    {                        
                        if (sqrt((z-rz)*(z-rz)+(y-ry)*(y-ry)+(x-rx)*(x-rx))*gridSpacing <= radius)
                        {
                            int icr = ChangeIndex(x, y, z); // Get index for current point
                            grid[icr] = V;
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
int VoltChargeGrid::ChangeIndex(int x, int y, int z)
{
    return x*gridSize*gridSize+y*gridSize+z;
}

// Method to calculate the voltage from the grid
void VoltChargeGrid::Relaxation()
{
    for (int i = 0; i < numberOfIterations; i++)
    {
        if (D3)
        {
            for (int z = 1; z < gridSize-2; z++)
            {
                for (int y = 1; y < gridSize-2; y++)
                {
                    for (int x = 1; x < gridSize-2; x++)
                    {
                        // Change origin from problem to code for the six spaces surrounding point charge
                        int icr = ChangeIndex(x,y,z);
                        int ir1 = ChangeIndex(x+1,y,z);
                        int ir2 = ChangeIndex(x-1,y,z);
                        int ir3 = ChangeIndex(x,y+1,z);
                        int ir4 = ChangeIndex(x,y-1,z);
                        int ir5 = ChangeIndex(x,y,z+1);
                        int ir6 = ChangeIndex(x,y,z-1);

                        grid[icr] = 1/6*(grid[ir1]+grid[ir2]+grid[ir3]+grid[ir4]+grid[ir5]+grid[ir6]);
                    }
                }

                // Keep point charges and surface voltages
                // VoltChargeGrid::AddChargeGrid();
                VoltChargeGrid::AddVoltageCircleGrid();
            }
        }
        else
        {
            for (int y = 1; y < gridSize-2; y++)
            {
                for (int x = 1; x < gridSize-2; x++)
                {
                    // Change origin from problem to code for the six spaces surrounding point charge
                    int icr = ChangeIndex(x,y,0);
                    int ir1 = ChangeIndex(x+1,y,0);
                    int ir2 = ChangeIndex(x-1,y,0);
                    int ir3 = ChangeIndex(x,y+1,0);
                    int ir4 = ChangeIndex(x,y-1,0);

                    grid[icr] = 1/4*(grid[ir1]+grid[ir2]+grid[ir3]+grid[ir4]);
                }

                // Keep point charges and surface voltages
                // VoltChargeGrid::AddChargeGrid();
                VoltChargeGrid::AddVoltageCircleGrid();
            }
        }
    }
}

void VoltChargeGrid::SaveResults()
{
    // Initialize file handling
    ofstream voltage(filename);

    for (int z = 0; z < gridSize; z++) 
    {
        for (int y = 0; y < gridSize; y++) 
        {
            for (int x = 0; x < gridSize; x++) 
            {
                int icr = ChangeIndex(x,y,z);
                // Write: x y z value
                voltage << x << " " << y << " " << z << " " << grid[icr] << "\n";
            }
            
            // One blank line after each "row" in a slice
            voltage << "\n";
        }
        
        // Two blank lines after each 2D "slice"
        voltage << "\n\n";
    }

    voltage.close();
}
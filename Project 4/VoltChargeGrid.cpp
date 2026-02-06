/*
Class VoltChargeGrid

Solves for the voltage of the grids

This code has limitations in the form of iterations, and how big the box is.
Having more iterations results in a better relaxation at the cost of increased time.
The size of the box will change how much it can relax to zero since there can be more or
less space.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/6/2026
*/

#include "VoltChargeGrid.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace VCG;

// Give initial parameters
VoltChargeGrid::VoltChargeGrid(double GridSpacing, int GridSize, int NumberOfIterations, bool DD3, std::string Filename) : 
                                gridSpacing(GridSpacing), gridSize(GridSize), 
                                numberOfIterations(NumberOfIterations), D3(DD3), filename(Filename), 
                                grid(gridSize*gridSize*gridSize, 0.0)
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
        int ir0 = ChangeIndex(x,y,z);
        int ir1 = ChangeIndex(x+1,y,z);
        int ir2 = ChangeIndex(x-1,y,z);
        int ir3 = ChangeIndex(x,y+1,z);
        int ir4 = ChangeIndex(x,y-1,z);
        int ir5 = ChangeIndex(x,y,z+1);
        int ir6 = ChangeIndex(x,y,z-1);

        // Calculate voltage from charge
        double v = VoltageFromPointCharge(q, gridSpacing);

        // Place voltage from charge to adjoining grid points
        grid[ir0] = v;
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

        if (D2 == 0)
        {
            for (int y = 0; y < gridSize; y++)
            {
                for (int x = 0; x < gridSize; x++)
                {
                    double gx = x-offset;
                    double gy = y-offset;
                    if (sqrt((gy-ry)*(gy-ry)+(gx-rx)*(gx-rx)) <= radius)
                    {
                        int icr = ChangeIndex(gx, gy, 0); // Get index for current point
                        grid[icr] = V;
                    }
                }
            }
        } 
        else
        {
            for (int z = 0; z < gridSize; z++)
            {
                for (int y = 0; y < gridSize; y++)
                {
                    for (int x = 0; x < gridSize; x++)
                    {              
                        double gx = x-offset;
                        double gy = y-offset;
                        double gz = z-offset;

                        if (sqrt((gz-rz)*(gz-rz)+(gy-ry)*(gy-ry)+(gx-rx)*(gx-rx)) <= radius)
                        {
                            int icr = ChangeIndex(gx, gy, gz); // Get index for current point
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
    // Shift from physics-space (center origin) to array-space (corner origin)
    int arrayX = x + offset;
    int arrayY = y + offset;
    int arrayZ = z + offset;

    // Safety check: If a calculation lands outside the box, 
    // we clamp it or return a safe 'boundary' index to prevent a Segfault.
    if (arrayX < 0) arrayX = 0; if (arrayX >= gridSize) arrayX = gridSize - 1;
    if (arrayY < 0) arrayY = 0; if (arrayY >= gridSize) arrayY = gridSize - 1;
    if (arrayZ < 0) arrayZ = 0; if (arrayZ >= gridSize) arrayZ = gridSize - 1;

    return arrayX * gridSize * gridSize + arrayY * gridSize + arrayZ;
}

// Method to calculate the voltage from the grid
void VoltChargeGrid::Relaxation()
{
    int start = -(offset-1);
    int end = offset;

    for (int i = 0; i < numberOfIterations; i++)
    {
        if (D3)
        {
            for (int z = start; z < end; z++)
            {
                for (int y = start; y < end; y++)
                {
                    for (int x = start; x < end; x++)
                    {
                        // Change origin from problem to code for the six spaces surrounding point charge
                        int icr = ChangeIndex(x,y,z);
                        int ir1 = ChangeIndex(x+1,y,z);
                        int ir2 = ChangeIndex(x-1,y,z);
                        int ir3 = ChangeIndex(x,y+1,z);
                        int ir4 = ChangeIndex(x,y-1,z);
                        int ir5 = ChangeIndex(x,y,z+1);
                        int ir6 = ChangeIndex(x,y,z-1);

                        grid[icr] = 1.0/6.0*(grid[ir1]+grid[ir2]+grid[ir3]+grid[ir4]+grid[ir5]+grid[ir6]);
                    }
                }
            }
        }
        else
        {
            for (int y = start; y < end; y++)
            {
                for (int x = start; x < end; x++)
                {
                    // Change origin from problem to code for the six spaces surrounding point charge
                    int icr = ChangeIndex(x,y,0);
                    int ir1 = ChangeIndex(x+1,y,0);
                    int ir2 = ChangeIndex(x-1,y,0);
                    int ir3 = ChangeIndex(x,y+1,0);
                    int ir4 = ChangeIndex(x,y-1,0);

                    grid[icr] = 1.0/4.0*(grid[ir1]+grid[ir2]+grid[ir3]+grid[ir4]);
                }
            }
        }
        // Keep point charges and surface voltages
        VoltChargeGrid::AddChargeGrid();
        VoltChargeGrid::AddVoltageCircleGrid();
    }
    VoltChargeGrid::SaveResults();
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
                int icr = x*gridSize*gridSize+y*gridSize+z;
                // Write: x y z value
                voltage << (x-offset)*gridSpacing << " " << (y-offset)*gridSpacing << " " << (z-offset)*gridSpacing << " " << grid[icr] << "\n";
            }
            
            // One blank line after each "row" in a slice
            voltage << "\n";
        }
        
        // Two blank lines after each 2D "slice"
        voltage << "\n\n";
    }

    voltage.close();
}
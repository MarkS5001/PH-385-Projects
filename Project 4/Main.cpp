/*
PH 385 Project 4 Main File

Models the voltage over a 2D or 3D grid of size 100cm (-50cm to 50cm) with a spacing of 2.5cm with charges,
and spots of constant voltage

The user inputs the size of the grid in grid space, spacing of the grid in m, charge of charges in C, 
placment of charges in grid space, voltage of voltage spots in V, and size of voltage spots in grid space.
This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/6/2026
*/
#include <iostream>
#include <ctime>
#include "VoltChargeGrid.cpp"

using namespace std;
using namespace VCG;

double gridSize = 40, gridSpacing = 2.5e-2; // Grid size in grid space and spacing in m
double charge1 = 1e-12, charge2 = 1e-12, charge3 = -1e-12, charge4 = -1e-12; // Charge in C
int rx1 = 10, ry1 = 0; // Position of charge 1 in grid space
int rx2 = 0, ry2 = 10; // Position of charge 2 in grid space
int rx3 = -10, ry3 = 0; // Position of charge 1 in grid space
int rx4 = 0, ry4 = -10; // Position of charge 1 in grid space
int radius = 4; // Radius of disk of voltage in grid space
int voltCirclePosition = 0; // Position of center of voltage disk
double voltCircleVoltage = 0.25; // Voltage of disk in V
int rz = 0; // Position of all z components
int iterations = 100;

string filename2D = "resultsP4_2D.txt";
string filename3D = "resultsP4_3D.txt";

int main()
{
    clock_t start = clock(); // Get program start time

    // Initialize class for 2D grid
    VoltChargeGrid grid2D(gridSpacing, gridSize, iterations, true, filename2D); // true for 2D, false for 3D

    // Add charges
    grid2D.AddPointCharge(charge1, rx1, ry1, rz);
    grid2D.AddPointCharge(charge2, rx2, ry2, rz);
    grid2D.AddPointCharge(charge3, rx3, ry3, rz);
    grid2D.AddPointCharge(charge4, rx4, ry4, rz);
    grid2D.AddChargeGrid();

    // Add surface voltages
    grid2D.AddVoltageCircle(voltCircleVoltage, voltCirclePosition, voltCirclePosition, rz, radius, 0); // 0 for circle, any other number for sphere
    grid2D.AddVoltageCircleGrid();

    // Run simulation
    grid2D.Relaxation();

    // Initialize class
    VoltChargeGrid grid3D(gridSpacing, gridSize, iterations, false, filename3D); // true for 2D, false for 3D

    // Add charges
    grid3D.AddPointCharge(charge1, rx1, ry1, rz);
    grid3D.AddPointCharge(charge2, rx2, ry2, rz);
    grid3D.AddPointCharge(charge3, rx3, ry3, rz);
    grid3D.AddPointCharge(charge4, rx4, ry4, rz);
    grid3D.AddChargeGrid();

    // Add surface voltages
    grid3D.AddVoltageCircle(voltCircleVoltage, voltCirclePosition, voltCirclePosition, rz, radius, 0); // 0 for circle, anyother number for sphere
    grid3D.AddVoltageCircleGrid();

    // Run simulation
    grid3D.Relaxation();

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
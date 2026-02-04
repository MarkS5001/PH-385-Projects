/*
PH 385 Project 4 Main File

Models the voltage over a 3D grid of size 50cm with a spacing of 2.5cm with charges, and spots of constant voltage

The user inputs the size of the grid, spacing of the grid, charge of charges, 
placment of charges, voltage of voltage spots, and size of voltage spots.
This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/3/2026
*/
#include <iostream>
#include <ctime>
#include "VoltChargeGrid.cpp"

using namespace std;
using namespace VCG;

double size = 50, gridSpacing = 2.5; // Grid size and spacing in cm
double charge1 = 1, charge2 = 1, charge3 = -1, charge4 = -1; // Charge in uC
int rx1 = 25, ry1 = 0; // Position of charge 1 in cm
int rx2 = 0, ry2 = 25; // Position of charge 2 in cm
int rx3 = -25, ry3 = 0; // Position of charge 1 in cm
int rx4 = 0, ry4 = -25; // Position of charge 1 in cm
int radius = 10; // Radius of disk of voltage
int voltCirclePosition = 0; // Position of center of voltage disk
double voltCircleVoltage = 0.25; // Voltage of disk in V
int rz = 0; // Position of all z components

string filename = "resultsP4.txt";

int main()
{
    clock_t start = clock(); // Get program start time

    // Initialize class
    VoltChargeGrid grid(10, false, filename, 40);

    // Add charges
    grid.AddPointCharge(charge1, rx1, ry1, rz);
    grid.AddPointCharge(charge2, rx2, ry2, rz);
    grid.AddPointCharge(charge3, rx3, ry3, rz);
    grid.AddPointCharge(charge4, rx4, ry4, rz);
    // grid.AddChargeGrid();

    // Add surface voltages
    grid.AddVoltageCircle(voltCircleVoltage, voltCirclePosition, voltCirclePosition, rz, radius, 1);
    grid.AddVoltageCircleGrid();

    // Run simulation
    grid.Relaxation();

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
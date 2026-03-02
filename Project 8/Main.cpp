/*
PH 385 Project 8 Main File

Models the motion of molecules

The user inputs the mass of the ball, diameter of the ball, air density, drag
coefficient, initial position, initial velocity, spin angular velocity,
and time step, all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 3/2/2026
*/
#include <iostream>
#include <ctime>
#include "MolecularDynamics.hpp"

using namespace std;

int main()
{
    clock_t start = clock(); // Get program start time

    
    // Plot the data after running 
    // system("gnuplot -persistent PingPong_Plot.gp");

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
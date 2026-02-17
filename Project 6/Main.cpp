/*
PH 385 Project 6 Main File

Models the motion of solute in a solvent.

The user inputs the mass of the ball, diameter of the ball, air density, drag
coefficient, initial position, initial velocity, spin angular velocity,
and time step, all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/17/2026
*/
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    clock_t start = clock(); // Get program start time



    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
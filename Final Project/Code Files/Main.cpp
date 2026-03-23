/*
PH 385 Final Project Main File

Fluid mechanics simulation using smoothed particle hydrodynamics.

The user inputs . This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 3/23/2026
*/
#include <iostream>
#include <ctime>
#include "SPH.cpp"

using namespace std;

int main()
{
    clock_t start = clock(); // Get program start time



    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
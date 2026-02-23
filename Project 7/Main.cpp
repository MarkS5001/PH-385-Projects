/*
PH 385 Project 7 Main File

Models the magnetization of a solid using the Ising model.

The user inputs the size of the grid, duration, temperature (start and finish),
temperature step size, and filename to save to.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/23/2026
*/
#include <iostream>
#include <ctime>
#include "Ising.cpp"

using namespace std;

int main()
{
    clock_t start = clock(); // Get program start time

    

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
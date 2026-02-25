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

int gridSize10 = 10;
int gridSize20 = 20;//10;
int gridSize30 = 30;
int gridSize40 = 40;
int gridSize50 = 50;

int duration = 200;//50;
double startTemp = 0.01;
double endTemp = 4.0;
double tempStep = 0.01;

string filename10 = "resultsP7_10.txt";
string filename20 = "resultsP7_20.txt";
string filename30 = "resultsP7_30.txt";
string filename40 = "resultsP7_40.txt";
string filename50 = "resultsP7_50.txt";

int main()
{
    clock_t start = clock(); // Get program start time

    Ising model10(gridSize10, duration, startTemp, endTemp, tempStep, filename10);
    model10.CalculateIsing();

    Ising model20(gridSize20, duration, startTemp, endTemp, tempStep, filename20);
    model20.CalculateIsing();

    Ising model30(gridSize30, duration, startTemp, endTemp, tempStep, filename30);
    model30.CalculateIsing();

    Ising model40(gridSize40, duration, startTemp, endTemp, tempStep, filename40);
    model40.CalculateIsing();

    Ising model50(gridSize50, duration, startTemp, endTemp, tempStep, filename50);
    model50.CalculateIsing();

    time_t end = clock();// Get program start time
    cout << endl << (end-start)/CLOCKS_PER_SEC << " seconds" << endl; // Display how long it took to run

    return 0;
}
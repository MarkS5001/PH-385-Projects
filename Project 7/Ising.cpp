/*
Class Ising

Simulates the magnetization of a solid using the Ising model.

This code has limitations in the form of size due to ram limits,.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/23/2026
*/

#include "Ising.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace IS;

Ising::Ising(double GridSize, int Duration, double StartTemp, double EndTemp, double TempStep, string Filename) : 
            gridSize(GridSize), grid(GridSize*GridSize*GridSize, 1), duration(Duration), startTemp(StartTemp),
            endTemp(EndTemp), tempStep(TempStep), size(GridSize-1), filename(Filename){};

int Ising::ChangeIndex(int ix, int iy, int iz)
{
    return ix*gridSize*gridSize+iy*gridSize+iz;
}

double Ising::FlipEnergy(int ix, int iy, int iz)
{
    double il = ix-1; // Index for the left gird space
    double ir = ix+1; // Index for the right grid space
    double iw = iy+1; // Index for the forward grid space
    double ib = iy-1; // Index for the backward grid space
    double iu = iz+1; // Index for the up grid space
    double id = iz-1; // Index for the down grid space

    // Correct edge boundaries to loop back to the other side of the grid
    if (ix == 0)
    {
        il = size;
    }
    else if (ix == size)
    {
        ir = 0;
    }

    if (iy == 0)
    {
        ib = size;
    }
    else if (iy == size)
    {
        iw = 0;
    }

    if (iz == 0)
    {
        iu = size;
    }
    else if (iz == size)
    {
        id = 0;
    }

    int left = grid[ChangeIndex(il, iy, iz)];
    int right = grid[ChangeIndex(ir, iy, iz)];
    int forward = grid[ChangeIndex(ix, iw, iz)];
    int backward = grid[ChangeIndex(ix, ib, iz)];
    int up = grid[ChangeIndex(ix, iy, iu)];
    int down = grid[ChangeIndex(ix, iy, id)];

    double energy = grid[ChangeIndex(ix, iy, iz)]*(left+right+forward+backward+up+down);
    return energy;
}

void Ising::CalculateIsing()
{
    ofstream Mags(filename);

    for (double T = startTemp; T <= endTemp; T+=tempStep)
    {
        totalMag = 0; // Reset magnetization
        for (int step = 0; step < duration; step++)
        {
            for (int z = 0; z < gridSize; z++)
            {
                for (int y = 0; y < gridSize; y++)
                {
                    for (int x = 0; x < gridSize; x++)
                    {
                        double eFlip = FlipEnergy(x,y,z);
                        if (eFlip<0)
                        {
                            grid[ChangeIndex(x,y,z)]*=-1;
                        }
                        else
                        {
                            if (dist(gen)<=exp(-eFlip/T))
                            {
                                grid[ChangeIndex(x,y,z)]*=-1;
                            }
                        }
                        if (step == duration-1) // Save magnetization for the final step
                        {
                           totalMag += grid[ChangeIndex(x,y,z)];
                        }
                    }
                }
            }
        }
        Mags << totalMag/(gridSize*gridSize*gridSize) << " " << T << endl;
    }
    Mags.close();
}
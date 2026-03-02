/*
Class MolecularDynamics

Simulates the motion of molecules

This code has limitations in the form of time step.

Author: Mark Smith (smi20046@byui.edu)
Date: 3/2/2026
*/

#include "MolecularDynamics.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace MD;

MolecularDynamics::MolecularDynamics(int GridSize, int NumParticles, double DeltaEnergy, int Duration, 
                                    double CutoffLength, double TimeStep, string Filename) : 
                                    gridSize(GridSize), positions(NumParticles*2,0), oldPositions(NumParticles*2,0), 
                                    deltaEnergy(DeltaEnergy), duration(Duration), numParticles(NumParticles), 
                                    cutoffLength(CutoffLength), timeStep(TimeStep), filename(Filename){}

void MolecularDynamics::GivePositions(int NumParticle, double x, double y)
{
    positions[NumParticle*2] = x;
    positions[NumParticle*2+1] = y;

    oldPositions[NumParticle*2] = x+0.01;
    oldPositions[NumParticle*2+1] = y+0.01;
}

double MolecularDynamics::Distance(int NumParticle1, int NumParticle2)
{
    int x1 = positions[NumParticle1*2];
    int y1 = positions[NumParticle1*2+1];
    int x2 = positions[NumParticle2*2];
    int y2 = positions[NumParticle2*2+1];

    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

double MolecularDynamics::Force(double distance)
{
    return 24*(2/pow(distance, 13)-1/pow(distance, 7));
}

double MolecularDynamics::NewPosition(double r, double oldr, double force)
{
    return 2.0*r-oldr+force*timeStep*timeStep;
}

double MolecularDynamics::Energy(int NumParticle)
{
    // Calculate velocity
    int vx = (positions[NumParticle*2]-oldPositions[NumParticle*2])/(2.0*timeStep);
    int vy = (positions[NumParticle*2+1]-oldPositions[NumParticle*2+1])/(2.0*timeStep);

    // Get magnitude of velocity
    int v = sqrt(vx*vx+vy*vy);

    // Return energy of particle
    return 1.0/2.0*m*v*v;
}

void MolecularDynamics::Dynamics()
{
    ofstream Data(filename);
    int energy = 0;

    for (int i = 0; i<duration*2.0; i++)
    {
        temp = 0;

        for (int part1 = 0; part1<numParticles; part1++)
        {
            // Unpack positions
            int rx1 = positions[part1*2];
            int ry1 = positions[part1*2+1];

            // Make place to store force
            int Fx = 0;
            int Fy = 0;

            for (int part2 = 0; part2<numParticles; part2++)
            {
                if (part1 != part2) // Cannot accelerate itself
                {
                    if (Distance(part1, part2) < cutoffLength)
                    {
                        // Unpack positions of relevant particles
                        int rx2 = positions[part2*2];
                        int ry2 = positions[part2*2+1];

                        // Calculate forces in each direction
                        Fx += Force(rx2-rx1);
                        Fy += Force(ry2-ry1);
                    }
                }
            }
            // Unpack old positions
            int orx1 = oldPositions[part1*2];
            int ory1 = oldPositions[part1*2+1];

            // Update old positions, and increase energy for next step
            oldPositions[part1*2] = positions[part1*2]-deltaEnergy/numParticles;

            // Update new positions
            positions[part1*2] = NewPosition(rx1, orx1, Fx);
            positions[part1*2+1] = NewPosition(ry1, ory1, Fy);

            // Check boundaries (x then y)
            if (positions[part1*2] < 0)
            {
                positions[part1*2] += gridSize;
            }

            if (positions[part1*2] > gridSize)
            {
                positions[part1*2] -= gridSize;
            }

            if (positions[part1*2+1] < 0)
            {
                positions[part1*2+1] += gridSize;
            }

            if (positions[part1*2+1] > gridSize)
            {
                positions[part1*2+1] -= gridSize;
            }

            if (i/10 == 0) // Save every 10 iterations
            {
                Data << positions[part1*2] << " " << positions[part1*2+1]; // Save x, y

                if (part1 != numParticles-1)
                {
                    Data << endl;
                }
                else // Keep line open so I can add the temperature and energy on the last line
                {
                    Data << " ";
                }
            }

            // Calculate temp
            temp += Energy(part1);
        }
        // Calculate temp and energy
        temp /= numParticles;

        if (i < duration) // Switch to subtract energy halfway through
        {
            energy += deltaEnergy;
        }
        else
        {
            energy -= deltaEnergy;
        }
        // Save temp, and energy
        Data << temp << " " << energy << endl << endl;
    }
    Data.close();
}
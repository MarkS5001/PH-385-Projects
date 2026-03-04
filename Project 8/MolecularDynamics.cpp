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

    oldPositions[NumParticle*2] = x;
    oldPositions[NumParticle*2+1] = y;
}

double MolecularDynamics::Distance(int NumParticle1, int NumParticle2)
{
    double x1 = positions[NumParticle1*2];
    double y1 = positions[NumParticle1*2+1];
    double x2 = positions[NumParticle2*2];
    double y2 = positions[NumParticle2*2+1];

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
    double vx = (positions[NumParticle*2]-oldPositions[NumParticle*2])/timeStep;
    double vy = (positions[NumParticle*2+1]-oldPositions[NumParticle*2+1])/timeStep;

    // Return energy of particle
    return 1.0/2.0*m*(vx*vx+vy*vy);
}

void MolecularDynamics::Dynamics()
{
    ofstream Data(filename);
    double energy = 0;

    // Save initial positions
    for (int part = 0; part < numParticles; part++)
            {
                Data << positions[part*2] << " " << positions[part*2+1]; // Save x, y

                if (part != numParticles-1)
                {
                    Data << endl;
                }
                else // Keep line open so I can add the temperature and energy on the last line
                {
                    Data << " " << temp << " " << energy << endl << endl << endl;
                }
            }


    for (int i = 0; i<duration*2.0; i++)
    {
        temp = 0;

        for (int part1 = 0; part1<numParticles; part1++)
        {
            // Unpack positions
            double rx1 = positions[part1*2];
            double ry1 = positions[part1*2+1];

            // Make place to store force
            double Fx = 0;
            double Fy = 0;

            for (int part2 = 0; part2<numParticles; part2++)
            {
                if (part1 != part2) // Cannot accelerate itself
                {
                    // Calculate minimum distance
                    double dx = positions[part2*2]-rx1;
                    double dy = positions[part2*2+1]-ry1;
                    if (dx > gridSize/2.0)
                    {
                        dx -= gridSize;
                    }
                    if (dx < -gridSize/2.0) 
                    {
                        dx += gridSize;
                    }
                    if (dy > gridSize/2.0) 
                    {
                        dy -= gridSize;
                    }
                    if (dy < -gridSize/2.0) 
                    {
                        dy += gridSize;
                    }

                    double r = sqrt(dx*dx+dy*dy);
                    if (r < cutoffLength)
                    {
                        // Unpack positions of relevant particles
                        double rx2 = positions[part2*2];
                        double ry2 = positions[part2*2+1];

                        // Calculate forces in each direction
                        double F = Force(r);
                        Fx += F*dx/r;
                        Fy += F*dy/r;
                    }
                }
            }
            // Unpack old positions
            double orx1 = oldPositions[part1*2];
            double ory1 = oldPositions[part1*2+1];

            double scale = (i < duration) ? (1.0 + deltaEnergy) : (1.0 - deltaEnergy);
            double adjusted_orx1 = rx1 - (rx1 - orx1) * scale;
            double adjusted_ory1 = ry1 - (ry1 - ory1) * scale;

            // Update new positions
            positions[part1*2] = NewPosition(rx1, adjusted_orx1, Fx);
            positions[part1*2+1] = NewPosition(ry1, adjusted_ory1, Fy);

            // Update old positions
            oldPositions[part1*2] = rx1;
            oldPositions[part1*2+1] = ry1;

            // Check boundaries (x then y)
            if (positions[part1*2] < 0)
            {
                positions[part1*2] += gridSize;
                oldPositions[part1*2] += gridSize;
            }

            if (positions[part1*2] > gridSize)
            {
                positions[part1*2] -= gridSize;
                oldPositions[part1*2] -= gridSize;
            }

            if (positions[part1*2+1] < 0)
            {
                positions[part1*2+1] += gridSize;
                oldPositions[part1*2+1] += gridSize;
            }

            if (positions[part1*2+1] > gridSize)
            {
                positions[part1*2+1] -= gridSize;
                oldPositions[part1*2+1] -= gridSize;
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
        if (i%10 == 0) // Save every 10 iterations
            {
                for (int part = 0; part < numParticles; part++)
                {
                    Data << positions[part*2] << " " << positions[part*2+1]; // Save x, y

                    if (part != numParticles-1)
                    {
                        Data << endl;
                    }
                    else // Keep line open so I can add the temperature and energy on the last line
                    {
                        Data << " " << temp << " " << energy << endl << endl << endl;
                    }
                }
            }
    }
    Data.close();
}
/*
Class Diffusion

Simulates the motion of a solute in a solvent.

This code has limitations in the form of time step. The particles
move in discrete amounts due to this time step, so the motion lacks
nuances that would be displayed from having the particles move according
to their own velocity.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/17/2026
*/

#include "Diffusion.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace Diff;

Diffusion::Diffusion(double Boundary, double Duration, double rStep, string Filename) : 
                    boundary(Boundary), duration(Duration), rstep(rStep), filename(Filename) {}

void Diffusion::AddParticle(double x, double y, double z)
{
    Particle newParticle(x, y, z);

    particles.push_back(newParticle);

    size = particles.size();
}

double Diffusion::GetRandomDirection()
{
    return dist(gen);
}

void Diffusion::MoveParticle()
{
    for (int i = 0; i < size; i++)
    {
        // Unpack particle
        Particle& currentParticle = particles[i];

        double x = currentParticle.Getx();
        double y = currentParticle.Gety();
        double z = currentParticle.Getz();

        // Get random theta and phi
        double theta = GetRandomDirection()/2.0;
        double phi = GetRandomDirection();

        // Set new positions
        double dx = rstep*sin(theta)*cos(phi);
        double dy = rstep*sin(theta)*sin(phi);
        double dz = rstep*cos(theta);
        double newx = x + dx;
        double newy = y + dy;
        double newz = z + dz;

        // Handle boundaries
        if (newx < -boundary || newx > boundary)
        {
            newx -= 2*dx;
        }
        if (newy < -boundary || newy > boundary)
        {
            newy -= 2*dy;
        }
        if (newz < -boundary || newz > boundary)
        {
            newz -= 2*dz;
        }

        currentParticle.Setx(newx);
        currentParticle.Sety(newy);
        currentParticle.Setz(newz);
    }
}

void Diffusion::Diffuse()
{
    ofstream Position(filename);

    // Loop through the duration
    for (int i = 0; i < duration; i++)
    {
        MoveParticle();

        // Save particle positions to file
        for (int i = 0; i < duration; i++)
        {
            Particle currentParticle = particles[i];

            double x = currentParticle.Getx();
            double y = currentParticle.Gety();
            double z = currentParticle.Getz();

            Position << x << " " << y << " " << z << endl;
        }
        Position << endl << endl;
    }
    Position.close();
}
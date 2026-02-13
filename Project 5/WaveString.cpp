/*
Class WaveString

Simulates the motion of a string including dampening, and stiffness
using Euler's method. 

This code has limitations in the form of the cromer value used (r).
This value is what sets the timestep. An improper setting can result
in outrageously values (most likely nan). When a lower cromer value
is used the code will take longer to run.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/13/2026
*/

#include "WaveString.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
using namespace WS;

WaveString::WaveString(int Segments, double SegmentLength, double epsilon, double Duration, double WaveSpeed, double r, double DampeningCoefficient, string Filename) : 
    segments(Segments), segmentLength(SegmentLength), stringValues(Segments, 0.0), timeStep(r*SegmentLength/WaveSpeed), 
    C1(2-2*r*r-6*epsilon*r*r*Segments*Segments), C2(r*r*(1+4*epsilon*Segments*Segments)), C3(-epsilon*r*r*Segments*Segments), C4(-2*DampeningCoefficient*timeStep),
    duration(Duration), dampeningCoefficient(DampeningCoefficient), filename(Filename)
{
    
}

double WaveString::GaussianFunction(double x, double amplitude, double width, double center)
{
    return amplitude*exp(-(x-center)*(x-center)/(2*width*width));
}

void WaveString::AddWave(double amplitude, double width, double center)
{
    for (int i = 0; i < segments; i++)
    {
        stringValues[i] += GaussianFunction(i*segmentLength, amplitude, width, center);
    }
}

void WaveString::CalculateStringPosition()
{
    int count = 0; // For saving

    double time = 0; // Tracks time of string evolution

    ofstream Position(filename); // For saving to file

    // Save initial values
    for (int i = 0; i < segments; i++)
    {
        // Position << i*segmentLength << " " << stringValues[i] << " " << time << endl;
        Position << i * segmentLength << " " << stringValues[i] << " " << std::fixed << std::setprecision(8) << time << endl;
    }
    Position << endl << endl;

    // Strings for calculating new position
    std::vector<double> stringPast = stringValues;
    std::vector<double> stringFuture(segments, 0.0);

    while (time < duration)
    {
        
        // Handle the boundaries
        stringFuture[1] = C1*stringValues[1]-stringPast[1]
                         +C2*(stringValues[1+1]+0.0)
                         +C3*(stringValues[1+2]-stringValues[1])
                         +C4*(stringValues[1]-stringPast[1]);

        stringFuture[segments-2] = C1*stringValues[segments-2]-stringPast[segments-2]
                                  +C2*(0.0+stringValues[segments-2-1])
                                  +C3*(-stringValues[segments-2]+stringValues[segments-2-2])
                                  +C4*(stringValues[segments-2]-stringPast[segments-2]);
        // Handle nonboundaries
        for (int i = 2; i < segments-2; i++)
        {
            stringFuture[i] = C1*stringValues[i]-stringPast[i]
                             +C2*(stringValues[i+1]+stringValues[i-1])
                             +C3*(stringValues[i+2]+stringValues[i-2])
                             +C4*(stringValues[i]-stringPast[i]);
        }
        /*//////////////////////////////////////////////////////////////////////////
        M=L/dx, r=c dt/dx

        C1*y[i,n]-y[i,n-1]
        +2*y[i,n]-2*r*r*y[i,n]-6*r*r*M*M*e*y[i,n]-y[i,n-1]

        C4(y[i,n]-y[i,n-1]); C4=-2*b*dt
        -2*b*dt*y[i,n]+2*b*dt*y[i,n-1]

        C2*(y[i+1]+y[i-1,n])
        +4*r*r*M*M*e*y[i+1,n]+r*r*y[i+1,n]+r*r*(1+4*e*M*M)*y[i-1,n]

        C3*(y[i+2,n]+y[i-2,n])
        -r*r*M*M*e*y[i+2,n]-r*r*M*M*e*y[i-2,n]

        //////////////////////////////////////////////////////////////////////////*/
        // Update values
        stringFuture[0] = 0;
        stringFuture[segments-1] = 0;
        stringPast = stringValues;
        stringValues = stringFuture;
        time += timeStep;
        count += 1;

        if (count%1/*00*/ ==0)
        {
            // Save new values
            for (int i = 0; i < segments; i++)
            {
                // Position << i*segmentLength << " " << stringValues[i] << " " << time << endl;
                Position << i * segmentLength << " " << stringValues[i] << " " << std::fixed << std::setprecision(8) << time << endl;
            }
            Position << endl << endl;
        }
    }
    Position.close();
}

void WaveString::SaveResults()
{
    ofstream Position(filename);

    for (int i = 0; i < segments; i++)
    {
        Position << i*segmentLength << " " << stringValues[i] << endl;
    }

    Position.close();
}
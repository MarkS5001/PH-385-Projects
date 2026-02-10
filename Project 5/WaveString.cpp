/*
Class WaveString

Simulates the motion of a string including quadratic air
resistance, and the Magnus force using Euler's method.

This code has limitations in the form of time step. With the use of Euler's
method, h (the time step) squared terms are neglected, and these terms will add up.
You can also decrease the time step to decrease the error, however the number
of steps needed will increase if a user does this.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/9/2026
*/

#include "WaveString.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace WS;

WaveString::WaveString(int Segments, double SegmentLength, double epsilon, double Duration, double WaveSpeed, string Filename) : 
    segments(Segments), segmentLength(SegmentLength), stringValues(Segments, 0.0), C1(2-2-6*epsilon*Segments*Segments),
    C2((1+4*epsilon*Segments*Segments)), C3(-epsilon*Segments*Segments), timeStep(SegmentLength/WaveSpeed), 
    duration(Duration), filename(Filename)
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
    double time = 0; // Tracks time of string evolution

    // Strings for calculating new position
    std::vector<double> stringPast = stringValues;
    std::vector<double> stringFuture(segments, 0.0);

    while (time < duration)
    {
        stringFuture[1] = C1*stringValues[1]-stringPast[1]
                         +C2*(stringValues[1+1]+0.0)
                         +C3*(stringValues[1+2]-stringValues[1]);

        stringFuture[segments-2] = C1*stringValues[segments-2]-stringPast[segments-2]
                                  +C2*(0.0+stringValues[segments-2-1])
                                  +C3*(-stringValues[segments-2]+stringValues[segments-2-2]);
        for (int i = 2; i < segments-2; i++)
        {
            stringFuture[i] = C1*stringValues[i]-stringPast[i]
                             +C2*(stringValues[i+1]+stringValues[i-1])
                             +C3*(stringValues[i+2]+stringValues[i-2]);
        }
        stringFuture[0] = 0;
        stringFuture[segments-1] = 0;
        stringPast = stringValues;
        stringValues = stringFuture;
        time += timeStep;
    }
    // SaveResults();
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
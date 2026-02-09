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
        stringValues[i] = GaussianFunction(i*segmentLength, amplitude, width, center);
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
        for (int i = 1; i < segments; i++)
        {
            if (i == 1)
            {
                stringFuture[i] += C1*(stringValues[i]-stringPast[i]);
                stringFuture[i] += C2*(stringValues[i+1]+stringValues[i-1]);
                stringFuture[i] += C3*(stringValues[i+2]+stringValues[i]);
            }
            else if (i == segments-1)
            {
                stringFuture[i] += C1*(stringValues[i]-stringPast[i]);
                stringFuture[i] += C2*(stringValues[i+1]+stringValues[i-1]);
                stringFuture[i] += C3*(stringValues[i]+stringValues[i-2]);
            }
            else
            {
                stringFuture[i] += C1*(stringValues[i]-stringPast[i]);
                stringFuture[i] += C2*(stringValues[i+1]+stringValues[i-1]);
                stringFuture[i] += C3*(stringValues[i+2]+stringValues[i-2]);
            }
        }
        time += timeStep;
    }
    SaveResults();
}

void WaveString::SaveResults()
{
    ofstream Position(filename);

    for (int i = 0; i == segments; i++)
    {
        Position << stringValues[i] << endl;
    }

    Position.close();
}
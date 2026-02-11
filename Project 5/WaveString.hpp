/*
Header file for WaveString clas

Creates an outline of what the WaveString class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 2/10/2026
*/

#pragma once
#include <vector>
#include <array>
#include <cmath>

namespace WS
{
    class WaveString
    {
        private:
            std::vector<double> stringValues; // Holds string segment position
            int segments; // Number of segments the string has (saving it for looping)
            double segmentLength; // Length of each string segment (for Gaussian function calculation)
            double C1, C2, C3; // Coefficients for loop
            double timeStep; // Assumes string parameter (r) is equal to one
            double duration;
            double dampeningCoefficient;
            std::string filename;

        public:
            WaveString(int Segments, double SegmentLength, double epsilon, double Duration, double WaveSpeed, double r, double DampeningCoefficient, std::string Filename); // Gets initial parameters
            double GaussianFunction(double x, double amplitude, double width, double center); // Calculates Gaussian of wave
            void AddWave(double amplitude, double width, double center); // Adds initial position of wave to string
            void CalculateStringPosition(); // Loops through to calculate time developed state of string
            void SaveResults();
    };
}
/*
Header file for Ising class

Creates an outline of what the Ising class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 2/23/2026
*/

#pragma once
#include <vector>
#include <random>

namespace IS
{
    class Ising
    {
        private:
            int gridSize;
            int size;
            std::vector<int> grid;
            double totalMag = 0;
            int duration;
            double startTemp;
            double endTemp;
            double tempStep;
            std::string filename;

            // Variables for randomness
            std::mt19937 gen{std::random_device{}()}; // dist(gen) to get random number
            std::uniform_real_distribution<double> dist{0.0, 1.0};

        public:
            Ising(double GridSize, int Duration, double StartTemp, double EndTemp, double TempStep, std::string Filename); // Get initial parameters
            int ChangeIndex(int ix, int iy, int iz); // Changes the index to the flat vector
            double FlipEnergy(int ix, int iy, int iz); // Calculates the flip energy
            void CalculateIsing(); // Loops through the grid to flip the spins
    };
}
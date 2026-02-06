/*
Header file for VoltChargeGrid class

Creates an outline of what the VoltChargeGrid class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 2/6/2026
*/

#pragma once
#include <iostream>
#include <array>
#include <vector>

namespace VCG
{
    class VoltChargeGrid
    {
        private:
            double gridSpacing;
            int gridSize;
            int offset = gridSize/2;
            double k = 8.99e9; // Coulomb's constant (SI)
            // int numberOfPointCharges = 0;
            // int numberOfVoltageCircles = 0;
            bool D3;
            int numberOfIterations;
            std::string filename;
            std::vector<std::array<int, 3>> pointCharges;
            std::vector<double> pointChargesCharge;
            std::vector<std::array<int, 5>> voltageCircles;
            std::vector<double> voltageCirclesVoltage;

            std::vector<double> grid; // Grid

        public:
            VoltChargeGrid(double GridSpacing, int GridSize, int NumberOfIterations, bool DD3, std::string Filename);
            void AddPointCharge(double q, int rx, int ry, int rz);
            void AddChargeGrid();
            void AddVoltageCircle(double V, int rx, int ry, int rz, int radius, int D2);
            void AddVoltageCircleGrid();
            double VoltageFromPointCharge(double q, double r);
            int ChangeIndex(int x, int y, int z);
            // int ChageOrigin();
            void Relaxation();
            void SaveResults();
    };
}
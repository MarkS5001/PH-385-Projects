/*
Header file for VoltChargeGrid class

Creates an outline of what the VoltChargeGrid class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 2/3/2026
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
            double gridSpacing = 2.5;
            static constexpr int gridSize = 40;
            double offset = (gridSize*gridSpacing)/2.0;
            double k = 8.99e9; // Coulomb's constant (SI)
            // int numberOfPointCharges = 0;
            // int numberOfVoltageCircles = 0;
            bool D3;
            int numberOfIterations;
            std::string filename;
            std::vector<std::array<double, 4>> pointCharges;
            std::vector<std::array<double, 6>> voltageCircle;
            std::array<std::array<std::array<double, gridSize>, gridSize>, gridSize> grid = {0}; // 3D grid

        public:
            VoltChargeGrid(int NumberOfIterations, bool DD3, std::string Filename);
            void AddPointCharge(double q, double rx, double ry, double rz);
            void AddChargeGrid();
            void AddVoltageCircle(double V, double rx, double ry, double rz, double radius, double D2);
            void AddVoltageCircleGrid();
            double VoltageFromPointCharge(double q, double r);
            double ChangeIndex(double r);
            void Relaxation();
            void SaveResults();
    };
}
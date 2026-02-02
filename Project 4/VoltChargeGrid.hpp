/*
Header file for VoltChargeGrid class

Creates an outline of what the VoltChargeGrid class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 2/2/2026
*/

#pragma once
#include <array>

namespace VCG
{
    class VoltChargeGrid
    {
        private:
            double gridSpacing;
            static constexpr int gridSize = 40;
            double offset = (gridSize*gridSpacing)/2.0;
            double k = 8.99e9; // Coulomb's constant (SI)
            std::array<std::array<std::array<double, gridSize>, gridSize>, gridSize> grid = {0}; // 3D grid

        public:
            VoltChargeGrid(/*const double GridSize, */const double GridSpacing);
            void AddCharge(double q, double rx, double ry, double rz);
            void AddVoltageCircle(double V, double rx, double ry, double rz, double radius, bool D2 = true);
            double VoltageFromPointCharge(double q, double r);
            double ChangeIndex(double r);
            void Relaxation();
    };
}
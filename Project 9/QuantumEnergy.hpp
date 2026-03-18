/*
Header file for QuantumEnergy class

Creates an outline of what the QuantumEnergy class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 3/16/2026
*/

#pragma once
#include <vector>

namespace QE
{
    class QuantumEnergy
    {
        private:
            double wellSize; // Size of well
            std::string filename;
            double dx; // Step size
            std::vector<double> psi; // Value of wavefunction
            std::vector<double> positions; // x position of wavefunction
            double dE; // Step size of energy
            double nExcited; // n value of most excited state wanted
            std::vector<double> energies; // Hold values from energies

        public:
            QuantumEnergy(double WellSize, double Dx, double DE, double NExcited, std::string Filename);
            double Potential(int n, double x);
            void Normalize();
            void Shooting(int N);
            void Matching(int N);
            double Schrodinger(double last, double current, double energy, int n, double x);

    };
}
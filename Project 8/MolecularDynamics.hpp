/*
Header file for MolecularDynamics class

Creates an outline of what the MolecularDynamics class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 3/2/2026
*/

#pragma once
#include <vector>
#include <string>

namespace MD
{
    class MolecularDynamics
    {
        private:
            std::vector<double> positions;
            std::vector<double> oldPositions;
            int gridSize;
            int numParticles;
            double deltaEnergy;
            int duration;
            double cutoffLength;
            double temp;
            double timeStep;
            double m = 1.0;
            std::string filename;

        public:
            MolecularDynamics(int GridSize, int NumParticles, double DeltaEnergy, int Duration, double CutoffLength, double TimeStep, std::string Filename);
            void GivePositions(int NumParticle, double x, double y);
            double Distance(int NumParticle1, int NumParticle2);
            double Force(double distance);
            double NewPosition(double r, double oldr, double force);
            double Energy(int v);
            void Dynamics();
    };
}
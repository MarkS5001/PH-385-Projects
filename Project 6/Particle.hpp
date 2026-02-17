/*
Header file for Particle class

Creates an outline of what the Particle class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 2/17/2026
*/

#pragma once

namespace P
{
    class Particle
    {
        private:
            double r; // Distance from origin to particle
            double phi; // Angle around the azimuthal direction
        public:
            Particle(double R, double Phi);
            void Setr(double R);
            void Setphi(double Phi);
            double Getr();
            double Getphi();
    };
}
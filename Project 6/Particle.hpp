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
            double x;
            double y;
            double z;

        public:
            Particle(double X, double Y, double Z);
            void Setx(double X);
            void Sety(double Y);
            void Setz(double Z);
            double Getx();
            double Gety();
            double Getz();
    };
}
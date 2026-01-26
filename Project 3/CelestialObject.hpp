/*
Header file for CelestialObject class

Creates an outline of what the CelestialObject class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 1/26/2026
*/

#pragma once
#include <vector>

namespace CO
{
    class CelestialObject
    {
        private:
            double mass;
            double radius;
            double velocity;

        public:
            // Initialize the parameters
            CelestialObject(const double Mass, const double Radius, const double Velocity);

            // Methods to set the parameters
            void SetMass(double Mass);
            void SetRadius(double Radius);
            void SetVelocity(double Velocity);

            // Methods to get the parameters
            double GetMass();
            double GetRadius();
            double GetVelocity();
    };
}
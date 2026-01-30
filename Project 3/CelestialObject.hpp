/*
Header file for CelestialObject class

Creates an outline of what the CelestialObject class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 1/30/2026
*/

#pragma once
#include <vector>

namespace CO
{
    class CelestialObject
    {
        private:
            double mass;
            double radius[2];
            double lastRadius[2];
            double velocity[2];
            double acceleration[2];

        public:
            // Initialize the parameters
            CelestialObject(const double Mass, const double RadiusX, const double RadiusY, 
                            const double VelocityX, const double VelocityY);

            // Methods to set the parameters
            void SetMass(double Mass);
            void SetRadiusX(double RadiusX);
            void SetRadiusY(double RadiusY);
            void SetLastRadiusX(double lastRadiusX);
            void SetLastRadiusY(double lastRadiusY);
            void SetVelocityX(double VelocityX);
            void SetVelocityY(double VelocityY);
            void SetAccelerationX(double AccelerationX);
            void SetAccelerationY(double AccelerationY);

            // Methods to get the parameters
            double GetMass();
            double GetRadiusX();
            double GetRadiusY();
            double GetLastRadiusX();
            double GetLastRadiusY();
            double GetVelocityX();
            double GetVelocityY();
            double GetAccelerationX();
            double GetAccelerationY();
    };
}
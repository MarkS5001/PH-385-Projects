/*
Header file for CelestialSystem class

Creates an outline of what the CelestialSystem class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 1/30/2026
*/

#pragma once
#include <vector>
#include "CelestialObject.hpp"

using namespace CO;

namespace CS
{
    class CelestialSystem
    {
        private:
            double timeStep;
            double duration;
            std::string filename;
            double G = 4*3.1415*3.1415; // Universal gravitation constant
            std::vector<CelestialObject> celestialObjects;

        public:
            CelestialSystem(double TimeStep, double Duration, std::string Filename); // Constructor
            
            void AddCelestialObject(double mass, double radiusX, double radiusY, 
                                    double velocityX, double velocityY);
                                    
            // Methods to update object movement
            double AccelerationBetweenBodies(double mass, double distance);
            void TotalAcceleration();
            void VerletMethod();
            double CenterOfMassX();
            double CenterOfMassY();
            double VelocityOfCenterOfMassX();
            double VelocityOfCenterOfMassY();
            void CalculateCenterOfMassCorrection();
    };
}
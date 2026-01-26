/*
Header file for CelestialSystem class

Creates an outline of what the CelestialSystem class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 1/26/2026
*/

#pragma once
// #include <vector>

namespace CS
{
    class CelestialSystem
    {
        private:
            double sunMass = 1;
            double earthMass = 3.0027e-6;
            double jupiterMass = 9.54588e-4;


        public:
            CelestialSystem();
    };
}
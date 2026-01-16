/*
Header file for PingPong class

Creates an outline of what the PingPong class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 1/14/2026
*/

#pragma once
#include <vector>

namespace Pendulum
{
    class DrivenPendulum
    {
        private:
            // Given variables
            double mass;
            double length;
            double dampingCoefficient;
            double duration;
            double timeStep;
            double drivingForce;
            double drivingFrequency;
            std::string filename;
            const double g = 9.81; // Gravity

            // Variables for loops
            double k1, k2, k3, k4;
            double time;
            double theta;
            double omega;

        public:
            DrivenPendulum(const double Mass,
                            const double Length,
                            const double DampingCoefficient,
                            const double InitialAngle,
                            const double InitialAngularVelocity,
                            const double Duration,
                            const double TimeStep,
                            const double DrivingForce,
                            const double DrivingFrequency,
                            const std::string& Filename);
            void RungeKutta();
            double PhysicalPendulum(double currentTheta, double currentOmega);
            double Theta(double currentOmega);
            // int RK4(double theta, double time, double timestep, )
    };
}
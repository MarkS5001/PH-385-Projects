/*
Header file for PingPong class

Creates an outline of what the PingPong class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 1/14/2026
*/

#pragma once
#include <vector>
#include <functional>

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
            double k1o, k2o, k3o, k4o; // Runge-Kutta coefficients for omega
            double k1t, k2t, k3t, k4t; // Runge-Kutta coefficients for theta
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
            double PhysicalPendulum(double currentTheta, double currentOmega, double currentTime);
            double Theta(double currentOmega);
            // double RK4(double currentTheta, double currentOmega, double currentTime, double timestep, std::function<double(double, double, double)> PhysicalPendulum);
    };
}
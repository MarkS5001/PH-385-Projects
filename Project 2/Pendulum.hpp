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
            double mass;
            double length;
            double dampingCoefficient;
            double initialAngle;
            double initialAngularVelocity;
            double duration;
            double timeStep;
            double drivingForce;
            double drivingFrequency;
            
        public:
            DrivenPendulum(double Mass,
                            double Length,
                            double DampingCoefficient,
                            double InitialAngle,
                            double InitialAngularVelocity,
                            double Duration,
                            double TimeStep,
                            double DrivingForce,
                            double DrivingFrequency)
                            :
                            mass(Mass),
                            length(Length),
                            dampingCoefficient(DampingCoefficient),
                            initialAngle(InitialAngle),
                            initialAngularVelocity(InitialAngularVelocity),
                            duration(Duration),
                            timeStep(TimeStep),
                            drivingForce(DrivingForce),
                            drivingFrequency(DrivingFrequency)
                            {};
    };
}
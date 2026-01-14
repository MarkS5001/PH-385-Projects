#pragma once
#include <vector>

namespace PP
{
    class PingPong
    {
    private:
        // Initialize variables that the class will use from user input
        double mass;
        double diameter;
        double density;
        double drag_coefficient;
        std::vector<double> initial_position;
        std::vector<double> initial_velocity;
        std::vector<double> initial_spin;
        double time_step;
        std::string filename;
        
        // Initialize variables that will be used by the various functions in class
        double ax, ay, az; // Make acceleration

        double v, vx, vy, vz; // Make velocity

        double rx, ry, rz; // Make position

        double Fx, Fy, Fz; // Make force (for drag)

        double A = pow(diameter/2,2)*3.1415; // Make area
        double drag; // Make drag force
        double magnusForce[3]; // Make magnus force

    public:
        // Initialize functions

        // Constructor
        PingPong(double Mass, 
            const double Diameter, 
            const double Density, 
            const double Drag_coefficient, 
            const std::vector<double>& Initial_position, 
            const std::vector<double>& Initial_velocity, 
            const std::vector<double>& Initial_spin, 
            const double Time_step, 
            const std::string& Filename);

        void EulersMethod(); // Euler's method for loop
        double DragForce(double v, double vr); // Drag calculation
        void MagnusForce(); // Magnus calculation
    };
}
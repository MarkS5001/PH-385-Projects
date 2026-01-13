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

        double A; // Make area
        double drag; // Make drag
        double magnusForce[3]; // Make magnus force

    public:
        // Initialize functions
        PingPong(double Mass, // Constructor
            double Diameter, 
            double Density, 
            double Drag_coefficient, 
            std::vector<double> Initial_position, 
            std::vector<double> Initial_velocity, 
            std::vector<double> Initial_spin, 
            double Time_step, 
            std::string Filename);

        void EulersMethod(); // Euler's method for loop
        double DragForce(double v, double vr); // Drag calculation
        void MagnusForce(); // Magnus calculation
    };
}
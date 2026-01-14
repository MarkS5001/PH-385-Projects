#include "PingPong.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace PP;


// Define the constructor to assign initial parameters
PingPong::PingPong(double Mass, 
    const double Diameter, 
    const double Density, 
    const double Drag_coefficient, 
    const vector<double>& Initial_position, 
    const vector<double>& Initial_velocity, 
    const vector<double>& Initial_spin, 
    const double Time_step, 
    const string& Filename) 
    :
    mass(Mass),
    diameter(Diameter),
    density(Density),
    drag_coefficient(Drag_coefficient),
    initial_position(Initial_position),
    initial_velocity(Initial_velocity),
    initial_spin(Initial_spin),
    time_step(Time_step),
    filename(Filename)
{};

// Define loop logic
void PingPong::EulersMethod()
{
    // Unpack variables
    rx = initial_position[0];
    ry = initial_position[1];
    rz = initial_position[2];
    vx = initial_velocity[0];
    vy = initial_velocity[1];
    vz = initial_velocity[2];
    
    // Initialize file handling
    ofstream Positions(filename); 
    Positions << rx << "," << ry << "," << rz << "\n"; // Write initial values to file

    // Loop that will stop will when the ball hits the ground or if it goes too high (to avoid infinite loops)
    while(rz > 0 && rz < 100)
    {
        // Calculate drag
        v = sqrt(vx*vx+vy*vy+vz*vz);
        Fx = DragForce(v, vx);
        Fy = DragForce(v, vy);
        Fz = DragForce(v, vz);

        // Calculate magnus force
        MagnusForce();

        // Update acceleration
        ax = Fx/mass+magnusForce[0];
        ay = Fy/mass+magnusForce[1];
        az = Fz/mass+magnusForce[2]-9.8;

        // Update velocity
        vx += ax*time_step;
        vy += ay*time_step;
        vz += az*time_step;

        // Update position
        rx += vx*time_step;
        ry += vy*time_step;
        rz += vz*time_step;

        Positions << rx << "," << ry << "," << rz << "\n"; // Write new values to file
    };
    Positions.close(); // Close file when done
};

// Define drag calculation
double PingPong::DragForce(double v, double vr)
{
    A = pow(diameter/2,2)*3.1415;
    drag = -0.5*drag_coefficient*density*A*v*vr;
    return drag;
};

// Define magnus calculation
void PingPong::MagnusForce()
{
    magnusForce[0] = 0.04*(initial_spin[1]*vz-initial_spin[2]*vy);
    magnusForce[1] = 0.04*(initial_spin[2]*vx-initial_spin[0]*vz);
    magnusForce[2] = 0.04*(initial_spin[0]*vy-initial_spin[1]*vx);
};
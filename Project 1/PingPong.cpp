#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

class PingPong {
public:
    // Define the constructor
    PingPong(double Mass, double Diameter, double Density, double Drag_coefficient, std::vector<double> Initial_position, std::vector<double> Initial_velocity, std::vector<double> Initial_spin, double Time_step, std::string Filename)
    {
        mass = Mass;
        diameter = Diameter;
        density = Density;
        drag_coefficient = Drag_coefficient;
        initial_position = Initial_position;
        initial_velocity = Initial_velocity;
        initial_spin = Initial_spin;
        time_step = Time_step;
        filename = Filename;
    };

    void EulersMethod()
    {
        rx = initial_position[0];
        ry = initial_position[1];
        rz = initial_position[2];

        vx = initial_velocity[0];
        vy = initial_velocity[1];
        vz = initial_velocity[2];
        
        std::ofstream Positions(filename);
        Positions << rx << "," << ry << "," << rz << "\n"; // Write initial values to file

        // Loop that will stop will when the ball hits the ground
        while(rz > 0 && rz < 50)
        {
            // Calculate drag
            v = std::sqrt(vx*vx+vy*vy+vz*vz);
            Fx = Drag_Force(v, vx);
            Fy = Drag_Force(v, vy);
            Fz = Drag_Force(v, vz);

            // Calculate magnus force
            Magnus_Force();

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

    double Drag_Force(double v, double vr)
    {
        A = std::pow(diameter/2,2)*3.1415;
        drag = -0.5*drag_coefficient*density*A*v*vr;
        return drag;
    };

    void Magnus_Force()
    {
        magnusForce[0] = 0.04*(initial_spin[1]*vz-initial_spin[2]*vy);
        magnusForce[1] = 0.04*(initial_spin[2]*vx-initial_spin[0]*vz);
        magnusForce[2] = 0.04*(initial_spin[0]*vy-initial_spin[1]*vx);
    };

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
    double ax;
    double ay;
    double az;
    double vx;
    double vy;
    double vz;
    double rx;
    double ry;
    double rz;
    double Fx;
    double Fy;
    double Fz;
    double v;
    double A;
    double drag;
    double magnusForce[3];
};
#include <iostream>
#include <vector>
#include <fstream>

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
        while(rz > 0)
        {
            // Update acceleration
            // ax += vx*time_step;
            // ay += vy*time_step;
            // az += vz*time_step;

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
    double ax = 0;
    double ay = 0;
    double az = -9.8;
    double vx;
    double vy;
    double vz;
    double rx;
    double ry;
    double rz;
};
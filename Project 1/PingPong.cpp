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
        std::ofstream Positions(filename);
        // Loop that will stop will when the ball hits the ground
        while(initial_position[2] > 0)
        {
            // Update acceleration
            ax += vx*time_step;
            ay += vy*time_step;
            az += vz*time_step;

            // Update velocity
            vx += ax*time_step;
            vy += ay*time_step;
            vz += az*time_step;

            // Update position
            rx += vx*time_step;
            ry += vy*time_step;
            rz += vz*time_step;

            Positions << rx << "," << ry << "," << rz << "\n"; // Write line to file
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
    double ax;
    double ay;
    double az;
    double vx;
    double vy;
    double vz;
    double rx;
    double ry;
    double rz;
};
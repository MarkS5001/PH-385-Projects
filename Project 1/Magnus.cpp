/*

*/
#include <iostream>
#include <vector>
#include "PingPong.cpp"
#include <cstdlib> // Library to have gnuplot plot the data after running

// Initialize variables for user input
// double mass;
// double diameter;
// double density;
// double drag_coefficient;
// std::vector<double> initial_position(3);
// std::vector<double> initial_velocity(3);
// std::vector<double> initial_spin(3);
// double time_step;
// std::string filename;

// So I don't have to type every time (for testing purposes)
double mass = 2.7/1000; // kg
double diameter = 4/100; //cm
double density = 0;
double drag_coefficient = 0;
std::vector<double> initial_position = {0,0,10};
std::vector<double> initial_velocity = {15,5,15};
std::vector<double> initial_spin = {0,0,0};
double time_step = 0.01;
std::string filename = "resultsP1.txt";

void main(){
    // std::cout << "What is the mass of the ball in kg? ";
    // std::cin >> mass;

    // std::cout << "What is the diameter of the ping pong ball in m? ";
    // std::cin >> diameter;

    // std::cout << "What is the density of the air? ";
    // std::cin >> density;

    // std::cout << "What is the drag coefficient? ";
    // std::cin >> drag_coefficient;

    // std::cout << "What is the x initial position? ";
    // std::cin >> initial_position[0];

    // std::cout << "What is the y initial position? ";
    // std::cin >> initial_position[1];

    // std::cout << "What is the z initial position? ";
    // std::cin >> initial_position[2];

    // std::cout << "What is the x initial velocity? ";
    // std::cin >> initial_velocity[0];

    // std::cout << "What is the y initial velocity? ";
    // std::cin >> initial_velocity[1];

    // std::cout << "What is the z initial velocity? ";
    // std::cin >> initial_velocity[2];

    // std::cout << "What is the x initial spin? ";
    // std::cin >> initial_spin[0];

    // std::cout << "What is the y initial spin? ";
    // std::cin >> initial_spin[1];

    // std::cout << "What is the z initial spin? ";
    // std::cin >> initial_spin[2];

    // std::cout << "What is the time step? ";
    // std::cin >> time_step;

    // std::cout << "What filename will it be saved to? ";
    // std::cin >> filename;

    PingPong pingPong(mass, diameter, density, drag_coefficient, initial_position, initial_velocity, initial_spin, time_step, filename);
    pingPong.EulersMethod();

    // Plot the data after running
    system("gnuplot -persistent PingPong_Plot.gp");
}
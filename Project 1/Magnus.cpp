#include <iostream>
#include <vector>

// Initialize variables for user input
double mass;
double diameter;
double density;
double drag_coefficient;
double initial_position;
std::vector<double> initial_velocity;
std::vector<double> initial_spin;
double time_step;
std::string filename;

int Main(){
    std::cout << "What is the mass of the ball in kg? ";
    std::cin >> mass;

    std::cout << "What is the diameter of the ping pong ball in m? ";
    std::cin >> diameter;

    std::cout << "What is the density of the air";
    std::cin >> density;

    std::cin >> drag_coefficient;

    std::cin >> initial_position;

std::vector<double> initial_velocity;

std::vector<double> initial_spin;

    std::cin >> time_step;

    std::cin >> filename;
}
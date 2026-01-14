/*
PH 385 Project 1 Main File

Models the projectile motion of a ball in three dimensions, including
quadratic air resistance and the Magnus force.

The user inputs the mass of the ball, diameter of the ball, air density, drag
coefficient, initial position, initial velocity, spin angular velocity,
and time step, all in SI units. This is followed by an output file name.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/14/2026
*/

#include <iostream>
#include <vector>
#include "PingPong.cpp"
// #include <cstdlib> // Library to have gnuplot plot the data after running
using namespace std;

// Initialize variables for user input
double mass;
double diameter;
double density;
double drag_coefficient;
vector<double> initial_position(3);
vector<double> initial_velocity(3);
vector<double> initial_spin(3);
double time_step;
string filename;

// Variables for testing purposes
// double mass = 0.0027; // kg
// double diameter = 0.04; //cm
// double density = 1.27;
// double drag_coefficient = 0.5;
// vector<double> initial_position = {0,0,5};//{0,0,10};
// vector<double> initial_velocity = {4,4,10};//{15,5,15};
// vector<double> initial_spin = {-50,-100,100};//{-20,-40,20};
// double time_step = 0.001;
// string filename = "resultsP1.txt";

void main(){
    // Get the user input

    cout << "What is the mass of the ball in kg? ";
    cin >> mass;

    cout << "What is the diameter of the ping pong ball in m? ";
    cin >> diameter;

    cout << "What is the density of the air? ";
    cin >> density;

    cout << "What is the drag coefficient? ";
    cin >> drag_coefficient;

    cout << "What is the x initial position? ";
    cin >> initial_position[0];

    cout << "What is the y initial position? ";
    cin >> initial_position[1];

    cout << "What is the z initial position? ";
    cin >> initial_position[2];

    cout << "What is the x initial velocity? ";
    cin >> initial_velocity[0];

    cout << "What is the y initial velocity? ";
    cin >> initial_velocity[1];

    cout << "What is the z initial velocity? ";
    cin >> initial_velocity[2];

    cout << "What is the x initial spin? ";
    cin >> initial_spin[0];

    cout << "What is the y initial spin? ";
    cin >> initial_spin[1];

    cout << "What is the z initial spin? ";
    cin >> initial_spin[2];

    cout << "What is the time step? ";
    cin >> time_step;

    cout << "What filename will it be saved to? ";
    cin >> filename;

    // Give starting conditions to the ping pong
    PingPong pingPong(mass, 
        diameter, 
        density, 
        drag_coefficient, 
        initial_position, 
        initial_velocity, 
        initial_spin, 
        time_step, 
        filename);
    
    // Run the Euler's method
    pingPong.EulersMethod();

    // Plot the data after running 
    // system("gnuplot -persistent PingPong_Plot.gp");
}
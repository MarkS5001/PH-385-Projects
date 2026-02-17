/*
Header file for Diffusion class

Creates an outline of what the Diffusion class defines

Author: Mark Smith (smi20046@byui.edu)
Date: 2/17/2026
*/

#pragma once
#include <vector>
#include <array>
#include <random>
#include "Particle.hpp"
using namespace P;

namespace Diff
{
    class Diffusion
    {
        private:
            std::vector<Particle> particles; // Stores postion of particles
            double boundary; // Boundary for the particles
            double duration; // How many steps the loop will run for
            double rstep; // How far the particles will move in the radial direction
            std::string filename; // File to save to
            int size; // Number of particles

            // Variables for randomness
            std::mt19937 gen{std::random_device{}()}; 
            std::uniform_real_distribution<double> dist{0.0, 2.0 * 3.1415};

        public:
            Diffusion(double Boundary, double Duration, double rStep, std::string Filename); // Get initial parameters
            void AddParticle(double x, double y, double z); // Adds a particle to the system
            double GetRandomDirection(); // Get the random direction
            void MoveParticle(); // Calculate the new particle position
            void Diffuse(); // Loop for the diffusion process
    };
}
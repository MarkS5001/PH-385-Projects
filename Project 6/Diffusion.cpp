/*
Class Diffusion

Simulates the motion of a solute in a solvent.

This code has limitations in the form of time step. With the use of Euler's
method, h (the time step) squared terms are neglected, and these terms will add up.
You can also decrease the time step to decrease the error, however the number
of steps needed will increase if a user does this.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/17/2026
*/

#include "class.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace Diff;
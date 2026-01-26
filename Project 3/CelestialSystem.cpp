/*
Class CelestialSystem

Simulates the motion of a multi-body system.

This code has limitations in the form of time step. With the use of Euler's
method, h (the time step) squared terms are neglected, and these terms will add up.
You can also decrease the time step to decrease the error, however the number
of steps needed will increase if a user does this.

Author: Mark Smith (smi20046@byui.edu)
Date: 1/26/2026
*/

#include "CelestialSystem.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace CS;
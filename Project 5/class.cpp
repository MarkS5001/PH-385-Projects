/*
Class PingPon

Simulates the projectile motion of a ball including quadratic air
resistance, and the Magnus force using Euler's method.

This code has limitations in the form of time step. With the use of Euler's
method, h (the time step) squared terms are neglected, and these terms will add up.
You can also decrease the time step to decrease the error, however the number
of steps needed will increase if a user does this.

Author: Mark Smith (smi20046@byui.edu)
Date: 2/9/2026
*/

#include "class.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
using namespace Name;
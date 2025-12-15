#pragma once
#include"vector.h"
#include<cmath>

const static int MAX_NEWTON_ITER = 10000;
const static float NEWTON_FLOAT_TOLERANCE = 1e-6;
const static float NEWTON_GRADIENT_TOLERANCE = 1e-8; //Should be smaller than float tolerance
const static float MAX_STEP_SIZE = 1.0f; //Cannot be larger than 1.0 to ensure stability

namespace numerics{

//TO ADD: 
// - LINEAR SYSTEM SOLVER (GAUSSIAN ELIMINATION WITH PARTIAL PIVOTING) for both dense and sparse matrices
// - NONLINEAR SYSTEM SOLVER (NEWTON-RAPHSON METHOD)
// - ODE INTEGRATORS (FORWARD EULER, BACKWARD EULER, RUNGE-KUTTA 4)
// Possibly a sparse matrix class later on

vector forward_euler_step(vector (*vector_field)(const vector&), const vector& current_state, float dt );

}
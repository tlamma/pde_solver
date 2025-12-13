#pragma once
#include"vector.h"
#include<cmath>

const static int MAX_NEWTON_ITER = 10000;
const static float NEWTON_FLOAT_TOLERANCE = 1e-6;
const static float NEWTON_GRADIENT_TOLERANCE = 1e-8; //Should be smaller than float tolerance
const static float MAX_STEP_SIZE = 1.0f; //Cannot be larger than 1.0 to ensure stability

namespace numerics{

vector newton_method(float (*a_function)(const vector& ), const vector& initial_guess);

vector forward_euler_step(vector (*vector_field)(const vector&), const vector& current_state, float dt );
vector backward_euler_step(vector (*vector_field)(const vector&), const vector& current_state, float dt);
}
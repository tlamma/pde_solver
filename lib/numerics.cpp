#include"numerics.h"
#include<cmath>
#include<iostream>

//NEWTON METHOD

//INTEGRATION METHODS
vector numerics::forward_euler_step(vector (*vector_field)(const vector&), const vector& current_state, float dt ){
    return current_state + dt *vector_field(current_state);
}
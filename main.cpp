#include"lib/ode_integrator.h"
#include"numerics.h"
#include<iostream>
int main(){


    //i want to test integrate on one 2d ode system in x,y , dx/dt = -y , dy/dt = x
    vector (*vector_field)(const vector&) = [](const vector& x) -> vector {
        vector result(2);
        result[0] = -x[1];
        result[1] = x[0];
        return result;
    };

    int dimension = 2;
    vector initial_conditions(dimension, dimension, 1.0f); // initial condition x(0) = 1.0
    ode my_ode(dimension, vector_field);
    float time_step = 0.00001f;
    int n_frames = 100000;
    int n_steps_per_frame = 1000;
    std::string method = "forward_euler";
    ode_integrator integrator(my_ode, time_step, n_frames, n_steps_per_frame, method);
    integrator.set_initial_conditions(initial_conditions);
    integrator.integrate();
    integrator.save_states_to_module("analysis/simulation_results/results");
    // for(int i = 0; i < n_frames; i++){
    //     std::cout << "Time " << i * time_step << ": x = " << results[i][0] << std::endl;
    // }   
    
    return 0;
}
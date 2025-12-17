#pragma once
#include"ode.h"
#include<string>

vector forward_euler_step(vector (*vector_field)(const vector&),const vector& current_state);

class ode_integrator{
    private:
    ode system; //ODE system to integrate
    matrix states; // SHOULD BE A MATRIX?
    float dt; // time step
    int n_frames; //number of frames
    int n_steps_per_frame; //number of time steps
    std::string method; //integration method
    
    public:
    //CONSTRUCTORS
    ode_integrator(const ode& sys, float time_step, int n_frames, int n_steps_per_frame, std::string m);
    //METHODS
    matrix get_states() const;
    void set_initial_conditions(const vector& initial_condition);
    void save_states_to_txt(const std::string& filename) const;
    void save_states_to_module(const std::string& module_name) const;
    void integrate();
};
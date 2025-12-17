#pragma once
#include"pde.h"

class rde_1d_integrator{
    rde_1d system;
    matrix* states;
    matrix initial_condition;
    float dt; // time step
    int n_frames; //number of frames
    int n_steps_per_frame; //number of time steps
    std::string method;
    ode get_discrete_ode()const;
    ode_integrator get_discrete_integrator()const;

    public:
    rde_1d_integrator(rde_1d system, matrix initial_condition,float dt, int n_frames, int n_steps_per_frame, std::string method);
    void integrate();
       
};
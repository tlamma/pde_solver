#include"pde_integrator.h"

rde_1d_integrator::rde_1d_integrator(rde_1d system, matrix initial_condition, float dt, int n_frames, int n_steps_per_frame, std::string method = "forward_euler"):system(system),initial_condition(initial_condition),dt(dt),n_frames(n_frames), n_steps_per_frame(n_steps_per_frame), method(method){
    states = new matrix[system.get_lattice().get_num_points()];
    states[0] = initial_condition;
}

ode rde_1d_integrator::get_discrete_ode()const{
    
}

void rde_1d_integrator::integrate(){

}
#include"pde_integrator.h"

rde_1d_integrator::rde_1d_integrator(rde_1d system, matrix initial_condition, float dt, int n_frames, int n_steps_per_frame, std::string method):system(system),initial_condition(initial_condition),dt(dt),n_frames(n_frames), n_steps_per_frame(n_steps_per_frame), method(method){
    states = new matrix[n_frames];
    for (int i = 0; i < n_frames; i++)
    {
        states[i] = matrix(initial_condition.get_rows(), initial_condition.get_columns(), 0.0f);
    }
    states[0] = initial_condition;
}

ode rde_1d_integrator::get_discrete_ode()const{
    static rde_1d captured_system = system;  
    static int captured_dimension = captured_system.get_reaction().get_dimension();
    static int captured_n_pts = captured_system.get_lattice().get_num_points();
    static vector (*captured_reaction)(const vector&) = captured_system.get_reaction().get_field(); 
    vector (*discrete_field)(const vector&) = [](const vector& state) -> vector {
        vector result1(captured_dimension * captured_n_pts, 0.0f);
        for (int i = 0; i < captured_n_pts; i++) {
            vector local_state(captured_dimension, 0.0f);
            for (int j = 0; j < captured_dimension; j++) {
                local_state[j] = state[i * captured_dimension + j];
            }
            vector local_result = captured_reaction(local_state);
            for (int j = 0; j < captured_dimension; j++) {
                result1[i * captured_dimension + j] = local_result[j];
            }
        }
        vector result2(captured_dimension * captured_n_pts, 0.0f);
        for (int comp = 0; comp < captured_dimension; comp++) {
        vector component_state(captured_n_pts, 0.0f);
        for (int i = 0; i < captured_n_pts; i++) {
            component_state[i] = state[i * captured_dimension + comp];
        }
        vector component_diffusion = captured_system.get_lattice().laplacian(component_state);
        for (int i = 0; i < captured_n_pts; i++) {
            result2[i * captured_dimension + comp] = captured_system.get_diffusivities()[comp] * component_diffusion[i];
        }
    }
    return result1 + result2;
};
    return ode(captured_dimension * captured_n_pts, discrete_field);
}

void rde_1d_integrator::integrate(){
// first create ode_intgrator
    ode discrete_ode = get_discrete_ode();
    ode_integrator integrator(discrete_ode, initial_condition.unwind(), dt, n_frames, n_steps_per_frame, method);
    integrator.integrate();
    // then get states
    vector* flat_states = integrator.get_states();
    for (int frame = 0; frame < n_frames; frame++) {
        states[frame] = matrix(*flat_states, discrete_ode.get_dimension());
    }
}
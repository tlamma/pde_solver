#include"ode_integrator.h"
#include"numerics.h"
#include<cmath>
#include<iostream>
#include<fstream>
#include<chrono>
#include <iomanip>
//CONSTRUCTORS
ode_integrator::ode_integrator(const ode& sys, const vector& initial_condition, float time_step, int n_frames, int n_steps_per_frame, std::string m):system(sys),initial_condition(initial_condition),dt(time_step),n_frames(n_frames),n_steps_per_frame(n_steps_per_frame),method(m){
    states = new vector[n_frames];
    for (int i = 0; i < n_frames; i++) {
        states[i] = vector(sys.get_dimension());
    }
    states[0] = initial_condition;
}

//METHODS
vector* ode_integrator::get_states() const{
    return states;
}

void ode_integrator::save_states_to_txt(const std::string& filename) const{
    std::ofstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("Could not open file for writing.");
    }
    file << "NEWTON METHOD:" <<std::endl;
    file << "MAX_NEWTON_ITER:" << MAX_NEWTON_ITER <<std::endl;
    file << "NEWTON_FLOAT_TOLERANCE:" << NEWTON_FLOAT_TOLERANCE <<std::endl;
    file << "NEWTON_GRADIENT_TOLERANCE:" << NEWTON_GRADIENT_TOLERANCE <<std::endl;
    file << "MAX_STEP_SIZE:" << MAX_STEP_SIZE <<std::endl;
    file << "INTEGRATOR METHOD:" << method << std::endl;
    file << "TIME_STEP:" << dt << std::endl;
    file << "N_FRAMES:" << n_frames << std::endl;
    file << "N_STEPS_PER_FRAME:" << n_steps_per_frame << std::endl;
    file << "DATA:" << std::endl;
    for(int frame = 0; frame < n_frames; frame++){
        for(int i = 0; i < system.get_dimension(); i++){
            file << states[frame][i];
            if(i < system.get_dimension() - 1){
                file << ",";
            }
        }
        file << "\n";
    }
}   

void ode_integrator::save_states_to_module(const std::string& module_name) const{
    std::ofstream file(module_name + ".py");
    if(!file.is_open()){
        throw std::runtime_error("Could not open module file for writing.");
    }
    file << "import numpy as np"<<std::endl;
    file<<"# Simulation parameters\n\n";
    file<<"MAX_NEWTON_ITER = "<< MAX_NEWTON_ITER << std::endl;
    file<<"NEWTON_FLOAT_TOLERANCE = "<<NEWTON_FLOAT_TOLERANCE<<std::endl;
    file<<"NEWTON_GRADIENT_TOLERANCE = "<<NEWTON_GRADIENT_TOLERANCE<<std::endl;
    file << "MAX_STEP_SIZE = " << MAX_STEP_SIZE <<std::endl;
    file << "INTEGRATOR_METHOD = " << "\"" << method << "\"" << std::endl;
    file << "TIME_STEP = " << dt << std::endl;
    file << "N_FRAMES = " << n_frames << std::endl;
    file << "N_STEPS_PER_FRAME = " << n_steps_per_frame << std::endl;
    file << "# Auto-generated ODE integration results module\n\n";
    file << "states = np.array([\n";
    for(int frame = 0; frame < n_frames; frame++){
        file << "    [";
        for(int i = 0; i < system.get_dimension(); i++){
            file << states[frame][i];
            if(i < system.get_dimension() - 1){
                file << ", ";   
            }
        }
        file << "],\n";
    }
    file << "])\n"; 
}

// void ode_integrator::integrate(){
//     for(int frame = 1; frame < n_frames; frame++){
//         vector current_state = states[frame - 1];        
//         for(int step = 0; step < n_steps_per_frame; step++){
//             if(std::string(method) == "forward_euler"){
//                 current_state = numerics::forward_euler_step(system.get_field(), current_state, dt);
//             }
//             else if(std::string(method) == "backward_euler"){
//                 current_state = numerics::backward_euler_step(system.get_field(), current_state, dt);
//             }   
//             else{
//                 throw std::invalid_argument("Unknown integration method.");
//             }
//         }
//         states[frame] = current_state;
//     }
// }

void ode_integrator::integrate() {

    using clock = std::chrono::high_resolution_clock;

    auto global_start = clock::now();   // for ETA

    for (int frame = 1; frame < n_frames; frame++) {

        auto start = clock::now();

        // ---- integration step ----
        vector current_state = states[frame - 1];

        for (int step = 0; step < n_steps_per_frame; step++) {
            if (std::string(method) == "forward_euler") {
                current_state = numerics::forward_euler_step(system.get_field(), current_state, dt);
            }
            // else if (std::string(method) == "backward_euler") {
            //     current_state = numerics::backward_euler_step(system.get_field(), current_state, dt);
            // }
            else {
                throw std::invalid_argument("Unknown integration method.");
            }
        }

        auto end = clock::now();
        states[frame] = current_state;

        // ---- time measurements ----
        std::chrono::duration<double> frame_time = end - start;
        std::chrono::duration<double> elapsed_global = end - global_start;

        double avg_frame_time = elapsed_global.count() / frame;
        double frames_left = n_frames - frame - 1;
        double eta_seconds = avg_frame_time * frames_left;

        // ---- progress bar ----
        float progress = float(frame) / float(n_frames - 1);
        int barWidth = 50;
        int pos = int(barWidth * progress);

        std::cout << "\r[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] ";

        int percent = int(progress * 100.0);
        std::cout << std::setw(3) << percent << "%";

        // ---- frame timing ----
        std::cout << " | frame: " << std::fixed << std::setprecision(2)
                  << frame_time.count() << " s";

        // ---- ETA ----
        int eta_min = int(eta_seconds / 60.0);
        int eta_sec = int(eta_seconds) % 60;
        std::cout << " | ETA: " << eta_min << "m " << eta_sec << "s     ";

        std::cout.flush();
    }

    std::cout << "\nDone.\n";
}
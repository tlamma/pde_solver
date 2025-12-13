#include"numerics.h"
#include<cmath>
#include<iostream>

//NEWTON METHOD
vector numerics::newton_method(float (*a_function)(const vector&), const vector& initial_guess) {
    vector current_guess = initial_guess;
    for(int iter = 0; iter < MAX_NEWTON_ITER; iter++) {
        float f_value = a_function(current_guess);
        //std::cout << "Iteration " << iter << ": f_value = " << std::fabs(f_value) << std::endl;
          // Convergence check
        if(std::fabs(f_value) < NEWTON_FLOAT_TOLERANCE) {
           // std::cout << "Converged at iteration " << iter << std::endl;
            break;
        }
        // Numerical gradient (central difference)
        float h = NEWTON_FLOAT_TOLERANCE;  // step size
        vector gradient(current_guess.get_length());

        for(int i = 0; i < current_guess.get_length(); i++) {
            vector perturbed_plus = current_guess;
            perturbed_plus[i] += h;
            gradient[i] = (a_function(perturbed_plus) - a_function(current_guess)) / h;
           // std::cout << "Gradient[" << i << "] = " << gradient[i] << std::endl;
        }

        // Gradient norm
        float grad_norm_sq = gradient * gradient;
        float grad_norm = std::sqrt(grad_norm_sq); 

        //Handle near-zero gradient safely, or when the zero is also a local extremum
        if(grad_norm < NEWTON_GRADIENT_TOLERANCE) {
            if(std::fabs(f_value) < NEWTON_FLOAT_TOLERANCE) {
              //  std::cout << "Gradient near zero, but f_value small → treated as convergence" << std::endl;
                break;
            } else {
              //  std::cerr << "Iteration " << iter 
                //          << ": Gradient near zero but function not converged, stopping to avoid NaN" 
                  //        << std::endl;
                break; // stop instead of throwing
            }
        }

        // Compute Newton step
        vector step = (f_value / grad_norm) * gradient;

        // Optional: limit maximum step size
        float step_norm = std::sqrt(step * step);
        if(step_norm > MAX_STEP_SIZE) {
            step = (MAX_STEP_SIZE / step_norm) * step;
        }

        // Update guess safely
        current_guess = current_guess - step;
       // std::cout<<"Iteration: "<<iter<<", f_value: "<<f_value<<", Guess: "<<current_guess[0]<<","<<current_guess[1]<<std::endl;

        // Optional: debug output
    }

    return current_guess;
}

//INTEGRATION METHODS
vector numerics::forward_euler_step(vector (*vector_field)(const vector&), const vector& current_state, float dt ){
    return current_state + dt *vector_field(current_state);
}

vector numerics::backward_euler_step(vector (*vector_field)(const vector&),const vector& current_state, float dt ){
   static vector (*captured_vector_field)(const vector&);
    captured_vector_field = vector_field;
   static vector captured_current_state;
    captured_current_state = current_state;
   static float captured_dt;
    captured_dt = dt;       
   float (*square_residual)(const vector&) = +[](const vector& next_state){
    return (next_state - captured_dt*captured_vector_field(next_state) - captured_current_state)*(next_state - captured_dt*captured_vector_field(next_state) - captured_current_state);
   };
   return newton_method(square_residual, current_state);
}

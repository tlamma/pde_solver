#pragma once
#include"matrix.h"
    
class ode{
    private:
    int dimension; //dimension of the ODE system
    vector initial_conditions; //initial conditions
    vector (*field)(const vector&); //vector field function
    public:
    //CONSTRUCTORS
    ode(int dim, const vector& init_cond, vector (*f)(const vector&));
    //METHODS
    int get_dimension() const;
    vector get_initial_conditions() const;
    vector (*get_field() const)(const vector&);
    vector get_field_value( const vector& x) const;
    //FRIENDS
    
};
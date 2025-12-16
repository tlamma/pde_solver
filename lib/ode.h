#pragma once
#include"matrix.h"
    
class ode{
    private:
    int dimension; //dimension of the ODE system
    vector (*field)(const vector&); //vector field function
    public:
    //CONSTRUCTORS
    ode(int dim, vector (*f)(const vector&));
    //METHODS
    int get_dimension() const;
    vector (*get_field() const)(const vector&);
    vector get_field_value( const vector& x) const;
    //FRIENDS
    
};
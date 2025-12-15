#pragma once
#include"finite_elements.h"
#include"ode.h"

class rde_1d{
    private:
    lattice_1d grid;
    vector (*ode_field)(const vector&); //function pointer to vector field
    vector* initial_conditions;
    
    public:
    rde_1d(lattice_1d grid, vector (*ode_field)(const vector&), vector* initial_conditions);
    ode discretize() const;
};
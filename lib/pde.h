#pragma once
#include"finite_elements.h"
#include"ode.h"

class rde_1d{
    private:
    lattice_1d lattice;
    ode reaction;
    float* diffusivities;

    
    public:
    rde_1d(lattice_1d grid, ode reaction, float* diffusivities);
    rde_1d(const rde_1d& rde);
    lattice_1d get_lattice() const;
    ode get_reaction() const;
    float* get_diffusivities()const;
    int get_num_components()const;

};
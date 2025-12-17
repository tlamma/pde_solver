#include"pde.h"
rde_1d::rde_1d(lattice_1d lattice, ode reaction, float* diffusivities):lattice(lattice),reaction(reaction){
    diffusivities = new float[reaction.get_dimension()];
}

rde_1d::rde_1d(const rde_1d& rde):lattice(rde.lattice),reaction(rde.reaction),diffusivities(rde.diffusivities){}

lattice_1d rde_1d::get_lattice() const{
    return lattice;
 }

 ode rde_1d::get_reaction() const{
    return reaction;
 }
float* rde_1d::get_diffusivities()const{
    return diffusivities;
}

int rde_1d::get_num_components()const{
    return reaction.get_dimension();
}
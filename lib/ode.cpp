#include"ode.h"

//CONSTRUCTORS
ode::ode(int n_eqs, const vector& init_cond, vector (*f)(const vector&)):dimension(n_eqs),initial_conditions(init_cond),field(f){}
//METHODS
int ode::get_dimension() const{
    return dimension;
}   
vector ode::get_initial_conditions() const{
    return initial_conditions;
}
vector ode::get_field_value(const vector& x) const{
    return field(x);
}
vector (*ode::get_field() const)(const vector&){
    return field;
}
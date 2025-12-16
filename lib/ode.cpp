#include"ode.h"

//CONSTRUCTORS
ode::ode(int n_eqs, vector (*f)(const vector&)):dimension(n_eqs),field(f){}
//METHODS
int ode::get_dimension() const{
    return dimension;
}   
vector ode::get_field_value(const vector& x) const{
    return field(x);
}
vector (*ode::get_field() const)(const vector&){
    return field;
}
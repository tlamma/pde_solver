#include"finite_elements.h"
#include<cmath>

lattice_1d::lattice_1d(const lattice_1d& lattice): num_points(lattice.num_points), length(lattice.length), boundary(lattice.boundary){}

lattice_1d::lattice_1d(int n_points, float len, std::string boundary) : num_points(n_points), length(len), boundary(boundary) {} 

float lattice_1d::get_dx() const {
    return length / (num_points - 1);
}

int lattice_1d::get_num_points() const{
    return num_points;
}

std::string lattice_1d::get_boundary()const{
    return boundary;
}

vector lattice_1d::laplacian(const vector& v) const {
    float dx = get_dx();
    vector result(v.get_length());
    if(boundary == "open") {
        for(int i = 1; i < num_points - 1; i++) {
            result[i] = (v[i-1] - 2 * v[i] + v[i+1]);
        }
        result[0] = ( - v[0] + v[1]);
        result[num_points - 1] = (v[num_points - 2] - v[num_points - 1]);
    }
    else if(boundary == "periodic") {
        for(int i = 0; i < num_points; i++) {
        result[i] = (v[(i-1) % num_points] - 2 * v[i] + v[(i+1) % num_points]);
    }
    }
    else {
        throw std::invalid_argument("Unknown boundary condition: " + boundary);
    }
    return (1/ (dx*dx))*result; //scaling by 1/dx^2
}

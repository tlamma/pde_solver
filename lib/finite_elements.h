#pragma once
#include"matrix.h"
#include<string>


class lattice_1d{
    private:
    int num_points; //number of grid points per dimension
    float length; //length of the side of the cubic lattice
    std::string boundary;

    public:
    lattice_1d(int n_points, float len, std::string boundary);
    vector laplacian(const vector& v) const;
    float get_dx() const;
    // vector eigenmode(int n_mode) const;
};

/*
class lattice_2d{
    private:
    int num_points_x; //number of grid points in x direction
    int num_points_y; //number of grid points in y direction
    float length_x; //length of the side of the cubic lattice in x direction
    float length_y; //length of the side of the cubic lattice in y direction
    std::string boundary_x;
    std::string boundary_y;

    public:
    lattice_2d(int n_points_x, int n_points_y, float len_x, float len_y, std::string boundary_x, std::string boundary_y);
    vector laplacian(const vector& u) const;
    float get_dx() const;
    float get_dy() const;
    vector eigenmode(int n_mode_x, int n_mode_y) const;
};
*/




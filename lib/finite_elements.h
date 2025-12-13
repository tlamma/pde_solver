#pragma once
#include"matrix.h"


class 1d_grid{
    private:
    int num_points; //number of grid points
    float length; //length of the grid
    matrix adjacency_matrix; //adjacency matrix for the grid

    public:
    //CONSTRUCTORS
    1d_grid(); //default constructor
    1d_grid(int n, float a, float b); //n points from a to b
    //METHODS
    float get_point(int index) const; //get grid point at index
    int get_num_points() const; //get number of grid points
    matrix get_adjacency_matrix() const;
};
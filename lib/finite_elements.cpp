#include"finite_elements.h"

//CONSTRUCTORS
1d_grid::1d_grid():num_points(0),length(0),adjacency_matrix(matrix()){}
1d_grid::1d_grid(int n, float a, float b):num_points(n),length(b - a),adjacency_matrix(matrix(n,n)){
    if(n < 2){
        throw std::invalid_argument("Number of points must be at least 2.");
    }
    float step = (b - a) / (n - 1);
    for(int i = 0;i < n;i++){
        if(i > 0){
            adjacency_matrix[i][i - 1] = 1;
            adjacency_matrix[i - 1][i] = 1;
        }
    }
}
//METHODS
float 1d_grid::get_point(int index) const{
    if(index < 0 || index >= num_points){
        throw std::out_of_range("Index out of range.");
    }
    float step = length / (num_points - 1);
    return index * step;
}
int 1d_grid::get_num_points() const{
    return num_points;
}    

matrix 1d_grid::get_adjacency_matrix() const{
    return adjacency_matrix;
}

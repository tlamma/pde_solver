#pragma once
#include"vector.h"

class matrix{
    private:
    int rows;
    int columns;
    int capacity;
    vector* ptr; //pointer to an array of vectors

    public:
    //CONSTRUCTORS     
    matrix(); //default constructor
    ~matrix(); //destructor
    matrix(int n,int m,float x); //n rows, m columns initialized to x
    matrix(const matrix& m); //copy constructor
    matrix(int n,int m, int c); //n rows, m columns, capacity c
    //METHODS
    void append_row(const vector& new_row); //append row at the end
    void change_capacity(int c); //change capacity of the matrix
    int get_rows() const;
    int get_columns() const;
    //OPERATORS
    matrix& operator=(const matrix& m); //copy assignment
    vector& operator[](int index)const; //row access
    friend matrix operator+(const matrix& A, const matrix& B); //matrix addition
    friend matrix operator*(const matrix& A, const matrix& B); //matrix multiplication
    friend vector operator*(const matrix& A, const vector& v); //matrix-vector multiplication
    friend matrix operator*(float x, const matrix& A); //scalar multiplication
    //FRIENDS
    friend matrix transpose(const matrix& A); //matrix transposition
};
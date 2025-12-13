#pragma once
#include <stdexcept>

static const int std_flexibility = 10;

class vector{
    private:
    //ATTRIBUTES
    float* ptr;
    int length;
    int capacity;

    public:
    //CONSTRUCTORS
    vector(); //default constructor
    ~vector(); //destructor
    vector(int l); //length l
    vector(int l,int c); //length l, capacity c
    vector(const vector& v); //copy constructor
    vector(int l,int c,float x); //initialize all elements to x
    //METHODS
    void append(float new_element); //append element at the end
    void change_capacity(int c);
    int get_length() const;

    //OPERATORS
    vector& operator=(const vector& v); //copy assignment
    float& operator[](int index)const; //element access
    friend vector operator+(const vector& u,const vector& v); //vector addition
    friend float operator*(const vector& u, const vector& v); //dot product
    friend vector operator*(float x, const vector& v); //scalar multiplication
    friend vector operator-(const vector& u,const vector& v); //vector negation
    friend vector hadamard(const vector& u, const vector& v); //hadamard product

    //FRIENDS
    friend vector concatenate(const vector& u,const vector& v); //vector concatenation
    friend vector extract(int a, int b, const vector& v); //vector extraction

};


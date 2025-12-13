#include"vector.h"

//CONSTRUCTORS

vector::vector():length(0),capacity(std_flexibility){ptr = new float[capacity];}

vector::~vector(){
    delete [] ptr;
    ptr = nullptr;
}

vector::vector(int l):length(l),capacity(l + std_flexibility){ptr = new float[capacity];}

vector::vector(int l, int c):length(l),capacity(c){ptr = new float[capacity];}

vector::vector(const vector& v):length(v.length),capacity(v.capacity){ptr = new float[capacity];
    for(int i = 0;i < v.length;i++){
        ptr[i] = v.ptr[i];
    }
}

vector::vector(int l,int c,float x):length(l),capacity(c){ptr = new float[capacity];
    for(int i = 0;i<length;i++){
        ptr[i] = x;
    }   
}

void vector::append(float x){
    if(length < capacity){
        ptr[length] = x;
        length++;
    }
    else{
        capacity += std_flexibility;
        float* newptr = new float[capacity];
        for(int i = 0;i < length;i++){
            newptr[i] = ptr[i];
        };
        newptr[length] = x;
        length++;
        delete [] ptr;
        ptr = newptr;
    }
}

void vector::change_capacity(int c){
    if(c < length){
        throw std::invalid_argument("New capacity cannot be less than current length.");
    }
    float* newptr = new float[c];
    for(int i = 0;i < length;i++){
        newptr[i] = ptr[i];
    }
    delete [] ptr;
    ptr = newptr;
    capacity = c;

}

int vector::get_length() const{
    return length;
}

//OPERATORS
vector& vector::operator=(const vector& v){
    if(this != &v){
        delete [] ptr;
        length = v.length;
        capacity = v.capacity;
        ptr = new float[capacity];
        for(int i = 0;i < length;i++){
            ptr[i] = v.ptr[i];
        }
    }
    return *this;
}

float& vector::operator[](int i) const {
    return ptr[i];
}

vector operator+(const vector& u,const vector& v) {
    if (u.length != v.length) {
        throw std::invalid_argument("Vectors must be of the same length for addition.");
    }
    vector result(u.length, std::max(u.capacity, v.capacity));
    for (int i = 0; i < u.length; i++) {
        result[i] = u[i] + v[i];
    }
    return result;  
}

float operator*(const vector& u, const vector& v) {
    if (u.length != v.length) {
        throw std::invalid_argument("Vectors must be of the same length for dot product.");
    }
    float result = 0;
    for (int i = 0; i < u.get_length(); i++) {
        result += u[i] * v[i];
    }
    return result;  
}

vector operator*(float x, const vector& v) {
    vector result(v.get_length(), v.capacity);
    for (int i = 0; i < v.get_length(); i++) {
        result[i] = v[i] * x;
    }
    return result;  
}

vector operator-(const vector& u,const vector& v) {
    return u + (-1.0 * v); 
}

vector hadamard(const vector& u, const vector& v) {
    if (u.length != v.length) {
        throw std::invalid_argument("Vectors must be of the same length for Hadamard product.");
    }
    vector result(u.get_length(), std::max(u.capacity, v.capacity));
    for (int i = 0; i < u.get_length(); i++) {
        result[i] = u[i] * v[i];
    }
    return result;  
}

//FRIENDS

vector concatenate(const vector& u,const vector& v) {
    vector result(u.get_length() + v.get_length(), u.capacity + v.capacity);
    for (int i = 0; i < u.get_length(); i++) {
        result[i] = u[i];
    }
    for (int i = 0; i < v.get_length(); i++) {
        result[u.get_length() + i] = v[i];
    }
    return result;  
}

vector extract(int a, int b, const vector& v) {
    if (a < 0 || b >= v.get_length() || a > b) {
        throw std::out_of_range("Invalid indices for extraction.");
    }
    vector result(b - a + 1);
    for (int i = a; i <= b; i++) {
        result[i - a] = v[i];
    }
    return result;  
}
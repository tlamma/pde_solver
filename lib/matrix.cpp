#include"matrix.h"

//CONSTRUCTORS  
matrix::matrix():rows(0),columns(0),capacity(std_flexibility){ptr = new vector[capacity];}
matrix::~matrix(){
    delete [] ptr;
    ptr = nullptr;
}   
matrix::matrix(int n,int m,float x):rows(n),columns(m),capacity(std::max(n,m) + std_flexibility){
    ptr = new vector[capacity];
    for(int i = 0;i < rows;i++){
        ptr[i] = vector(m,m + std_flexibility,x);
    }
}
matrix::matrix(const matrix& m):rows(m.rows),columns(m.columns),capacity(m.capacity),ptr(new vector[capacity]){
    for(int i = 0;i < rows;i++){
        ptr[i] = m.ptr[i];
    }
}
matrix::matrix(int n,int m,int c):rows(n),columns(m),capacity(c),ptr(new vector[capacity]){
    for(int i = 0;i < rows;i++){
        ptr[i] = vector(m);
    }
}
matrix::matrix(const vector& v, int m):columns(m){
    if(v.get_length() % m != 0){
        throw std::invalid_argument("Vector length must be divisible by number of columns.");
    }
    rows = v.get_length() / m;
    capacity = rows + std_flexibility;
    ptr = new vector[capacity];
    for(int i = 0;i < rows;i++){
        ptr[i] = vector(m);
        for(int j = 0;j < m;j++){
            ptr[i][j] = v[i * m + j];   
        }
    }
}

//METHODS
void matrix::append_row(const vector& new_row){
    if(new_row.get_length() != columns){
        throw std::invalid_argument("New row must have the same number of columns.");
    }
    if(rows < capacity){
        ptr[rows] = new_row;
        rows++;
    }else{
        capacity += std_flexibility;
        vector* newptr = new vector[capacity];
        for(int i = 0;i < rows;i++){
            newptr[i] = ptr[i];  
        }
        newptr[rows] = new_row;
        rows++;
        delete [] ptr;
        ptr = newptr;
    }
}
void matrix::change_capacity(int c){
    if(c < rows){
        throw std::invalid_argument("New capacity cannot be less than current number of rows.");
    }
    vector* newptr = new vector[c];
    for(int i = 0;i < rows;i++){
        newptr[i] = ptr[i];
    }
    delete [] ptr;
    ptr = newptr;
    capacity = c;
}   

int matrix::get_rows() const{
    return rows;
}
int matrix::get_columns() const{
    return columns;
}

vector matrix::unwind() const{
    vector result(rows * columns);
    for(int j = 0;j < columns;j++){
        for(int i = 0;i < rows;i++){
            result.append(ptr[i][j]);
        }
    }
    return result;
}
//OPERATORS
matrix& matrix::operator=(const matrix& m) {
    if(this != &m) {
        delete[] ptr;               // free old memory
        rows = m.rows;
        columns = m.columns;
        capacity = m.capacity;
        ptr = new vector[capacity];
        for(int i = 0; i < rows; i++)
            ptr[i] = m.ptr[i];     // uses vector copy assignment
    }
    return *this;
}

vector& matrix::operator[](int index) const {
    return ptr[index];
}       
matrix operator+(const matrix& A, const matrix& B){
    if(A.rows != B.rows || A.columns != B.columns){
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }
    matrix result(A.rows,A.columns,std::max(A.capacity,B.capacity));
    for(int i = 0;i < A.rows;i++){
        result[i] = A[i] + B[i];
    }
    return result;
}
matrix operator*(const matrix& A, const matrix& B){
    if(A.columns != B.rows){
        throw std::invalid_argument("Number of columns of A must equal number of rows of B for multiplication.");
    }
    matrix result(A.rows,B.columns,std::max(A.capacity,B.capacity));
    for(int i = 0;i < A.rows;i++){
        for(int j = 0;j < B.columns;j++){
            float sum = 0;
            for(int k = 0;k < A.columns;k++){   
                sum += A[i][k] * B[k][j];
            }
            result.ptr[i].append(sum);
        }
    }
    return result;
}
vector operator*(const matrix& A, const vector& v){
    if(A.columns != v.get_length()){
        throw std::invalid_argument("Matrix columns must equal vector length for multiplication.");
    }
    vector result(A.rows);
    for(int i = 0;i < A.rows;i++){
        float sum = 0;              
        for(int j = 0;j < A.columns;j++){
            sum += A[i][j] * v[j];
        }
        result.append(sum);
    }
    return result;
}
matrix operator*(float x, const matrix& A){
    matrix result(A.rows,A.columns,A.capacity);
    for(int i = 0;i < A.rows;i++){          
        result[i] = x * A[i];
    }
    return result;
}
//FRIENDS   
matrix transpose(const matrix& A){
    matrix result(A.columns,A.rows,A.capacity);
    for(int i = 0;i < A.rows;i++){
        for(int j = 0;j < A.columns;j++){
            if(i == 0){
                result.ptr[j] = vector(A.rows);
            }
            result.ptr[j][i] = A.ptr[i][j];
        }
    }
    return result;
}
#ifndef SCIENTIFICCALCULATORLIB_H_INCLUDED
#define SCIENTIFICCALCULATORLIB_H_INCLUDED

#include<iostream>
#include<vector>
using namespace std;

double factorial(double);

class Matrix
{
public:
    Matrix():row{0},column{0} {}
    void operator+(Matrix);
    void operator-(Matrix);
    void operator*(Matrix);
    void read_matrix();
    void print();
    friend class Input_stream;
private:
    vector<double>values;
    unsigned row;
    unsigned column;
};

class Input_stream
{
public:
    void get(Matrix*);
    bool validate_operator();
    char symbol;
};


class Trigonometry
{
public:
    void read_trigonometry();
    double compute_trigonometry();
private:
    string trigonometry_function;
    double degree;
};

#endif // SCIENTIFICCALCULATORLIB_H_INCLUDED


#undef __STRICT_ANSI__          //Allows the use of PI constant from cmath header file

#include<iostream>
#include<vector>
#include<cmath>
#include "scientificCalculatorLib.h"
#include "error.h"

using namespace std;

Input_stream input_temp;        //Object to read the token in matrix environment

double factorial(double operand)
{
    double factorial_result=1;
    for(int current_number=operand; current_number>1; --current_number)
        factorial_result*=current_number;

    return factorial_result;
}


void Matrix::read_matrix()
{
    vector<int>columns;
    const char new_row=',';
    const char empty_symbol=0;
    const char expression_ending=';';

    while(true){
            input_temp.get(this);

            switch(input_temp.symbol){
                case new_row:
                    ++row;                                                      //Incrementing the row of the matrix
                    input_temp.symbol=empty_symbol;                             //Preparing expression symbol variable to store another symbol
                    columns.push_back(column);                                  //Storing the column size of the row
                    column=0;                                                   //Preparing to count the column of the next row
                    break;
                case expression_ending: case '+': case '-': case '*':
                    ++row;                                                      //Counting a row after an operation or expression ending symbol is read
                    columns.push_back(column);

                    if(equal(columns.begin()+1,columns.end(),columns.begin()))  //Ensuring the columns of each row of the matrix are equal
                        column=columns[0];                                      //The Column of the matrix is set to it's value
                    else
                        error("Unequal Columns");
                    return;
            }
    }

    return;
}

void Matrix::print()
{
    int counter=0;
    const char new_line ='\n';
    const char space_bar=32;

    cout<<"\t\t Matrix Operation Result\n\n";
    for(unsigned i=0; i<row; ++i){
        cout<<new_line;
        for(unsigned i=0; i<column; ++i){
            cout<<values[counter]<<space_bar;
            ++counter;
        }
    }

    return;
}

void Matrix::operator+(Matrix b)
{
    if(row==b.row && column==b.column)                                      //Checking that the dimension of two matrices are equal
        for(unsigned i=0; i<values.size(); ++i) values[i]+=b.values[i];
    else
        error("Matrices dimension unequal");

    return;
}

void Matrix::operator-(Matrix b)
{
    if(row==b.row && column==b.column)                                      //Checking that the dimension of two matrices are equal
        for(unsigned i=0; i<values.size(); ++i) values[i]-=b.values[i];
    else
        error("Matrices dimension unequal");

    return;
}

void Matrix::operator*(Matrix b)
{
    if(column!=b.row)                                                      // Checking that Column of first Matrix matches the row of the second Matrix
        error("Matrices should be of equal column and row");

    vector<int>answer;
    int current_row=0;
    int current_column=0;

    for(unsigned i=0; i<row; ++i){                                           //Selecting the  first matrix's rows
        int row_element=current_row;
        for(unsigned i=0; i<b.column; ++i){                                 //Selecting the second matrix's columns
            int column_element=current_column;
            int result=0;
            for(unsigned i=0; i<column; ++i){                               //Performing matrix multiplication of the chosen row and column
                result+=values[row_element]*b.values[column_element];
                ++row_element;                                              //Moving to the next element in the current row
                column_element+=b.column;                                   //Moving to the next element in the current column
            }
            answer.push_back(result);                                       //Storing the result of a matrix multiplication
            row_element=current_row;                                        //Choosing the current row again
            ++current_column;                                               //Choosing the next column
        }
        current_row+=column;                                                //Choosing the next row
        current_column=0;                                                   //Choosing the first column
    }

    column=b.column;                                                        //Making the final matrix have the column of the second matrix
    values.clear();                                                         //Storing the result of the matrix multiplication
    for(int i:answer) values.push_back(i);
}


void Input_stream::get(Matrix *temp)
{
    char input;
    double element_value=0;
    const int first_element=0;
    int element=temp->values.size();

    cin>>input;

    if(element==first_element){
        switch(input){
            case '0': case '1': case '2': case '3': case '4': case '-':
            case '5': case '6': case '7': case '8': case '9':
                cin.putback(input);
                cin>>element_value;
                temp->values.push_back(element_value);                                      //Adding value to the matrix
                ++(temp->column);                                                                   //Every element is a new column
                return;
            default:
                error("Wrong expression, first element of a matrix should be a number");
            }
        }

    switch(input){
        case '+': case '-': case '*':
            input_temp.symbol=input;
            return;
        case ',': case';':
            input_temp.symbol=input;
            break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            cin.putback(input);
            cin>>element_value;
            temp->values.push_back(element_value);
            ++(temp->column);
            return;
        default:
            error("Wrong expression, matrix should contain only a number");
    }

    return;
}

void Trigonometry::read_trigonometry()
{
    char input='0';
    const char first_letter_in_sine='s';
    const char first_letter_in_cosine='c';
    const char first_letter_in_tangent='t';
    const char opening_bracket='(';

    cin>>input;
    if(input==first_letter_in_sine || input==first_letter_in_cosine || input==first_letter_in_tangent){
        while(input!=opening_bracket){
            trigonometry_function+=input;                   //Forming the trigonometry function in words
            cin>>input;
        }

    }
    cin>>degree;

}


double Trigonometry::compute_trigonometry()
{
    int power=1;
    double result=0;
    double current=0;
    degree*=M_PI/180.0;                                                                            //Converting degree to radians
    const string sine="sin";
    const string cosine="cos";
    const int last_term=190;

    if(trigonometry_function==sine){
        for(int current_term=0; current_term<last_term; ++current_term){                           //Computing the terms in the Taylor's series until the 190th term
            current=pow(degree, power)/factorial(power);

            if(current_term%2==0)
                result+=current;
            else
                result-=current;

            power+=2;
        }
    }

    else if(trigonometry_function==cosine){
            power=0;
        for(int current_term=0; current_term<last_term; ++current_term){                           //Computing the terms in the Taylor's series until the 190th term
            current=pow(degree,power)/factorial(power);

            if(current_term%2==0)
                result+=current;
            else
                result-=current;

            power+=2;
        }
    }

    return result;
}




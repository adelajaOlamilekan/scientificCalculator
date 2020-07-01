
#include<iostream>
#include<iterator>
#include<cstdlib>
#include "scientificCalculatorLib.h"
#include "error.h"

using namespace std;

void matrix_expression();
void compute_matrix(Matrix&,Matrix&,char);
void main_menu();
bool no_more_character();
void trigonometric_expression();

extern Input_stream input_temp;


int main()
try{
    main_menu();
    cout<<"\n";
    system("pause");
    return 0;
}

catch(runtime_error message)
{
    cout<<message.what();
}


void main_menu()
{
    char option=0;
    bool no_leftover_character = true;              //Signifies that the user's input is only a character as expected
    const char first_option='1';
    const char second_option='2';

    cout<<"Choose the operation to be performed \n";
    cout<<"1. Matrix Operation \n";
    cout<<"2. Trigonometric Operations \n";
    cin>>option;

    no_leftover_character=no_more_character();     //Checking if there is no character left in the input line

    if(no_leftover_character){
    switch(option){
        case first_option:
            system("cls");
            cout<<"Enter a matrix matrix_expression Format: Mat A (operation) Mat B\n";
            matrix_expression();
            break;
        case second_option:
            system("cls");
            cout<<"Enter the trigonometric expression. Format: sin(angle)\n";
            trigonometric_expression();
            break;
        default:
            error("Wrong Input, Enter 1 or 2");
        }
    }
    else
        error("Wrong input, Enter 1 or 2");
}

bool no_more_character()
{
    string extra_character;
    const char space_bar=32;
    bool is_whitespace_only=true;

    getline(cin,extra_character);

    //Checking if string contains only whitespace
    for(char character:extra_character){
        if(character!=space_bar){
            is_whitespace_only=false;
            break;
        }
    };

    if(extra_character.empty() || is_whitespace_only)  return true;
    else  return false;
}


void matrix_expression()
{
    const char terminate_expresssion=';';
    const char is_empty=0;

    Matrix a;
    a.read_matrix();

    while(input_temp.symbol!=terminate_expresssion){

        char operation=input_temp.symbol;
        input_temp.symbol=is_empty;
        Matrix b;
        b.read_matrix();
        compute_matrix(a,b,operation);
    }

    a.print();
}


void compute_matrix(Matrix &a, Matrix &b, char operation)
{
    const char addition='+';
    const char subtraction='-';
    const char multiplication='*';

    switch(operation){
        case addition:
            a+b;
            break;
        case subtraction:
            a-b;
            break;
        case multiplication:
            a*b;
    }
}

void trigonometric_expression()
{

    Trigonometry trig;

    trig.read_trigonometry();
    cout<<"The result is "<<trig.compute_trigonometry();

}



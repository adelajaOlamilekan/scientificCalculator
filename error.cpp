
#include<iostream>
#include "error.h"

void error(std::string message)
{
    throw std::runtime_error{message};
}

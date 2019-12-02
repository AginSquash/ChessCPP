//
//  debug_func.cpp
//  ChessCPP
//
//  Created by Vlad Vrublevsky on 21.10.2019.
//

#include "debug_func.hpp"

#include <iostream>

void _print(std::string var_name, int var)
{
    std::cout << "DEBUG: " << var_name << " = " << var << std::endl;
}

void _print(std::string var_name, std::string var)
{
    std::cout << "DEBUG: " << var_name << " = " << var << std::endl;
}

void _print(std::string var_name, float var)
{
    std::cout << "DEBUG: " << var_name << " = " << std::to_string(var)
              << std::endl;
}

#include <iostream>

#include "io_handler.h"

std::string io_handler::read()
{
    std::string input;
    getline(std::cin, input);

    return input;
}
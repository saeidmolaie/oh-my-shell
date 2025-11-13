#include <iostream>

#include "environment.h"
#include "io_handler.h"

#define PROMPT_PREFIX " at "
#define ARROW " ➜ "

std::string io_handler::read()
{
    write_shell_prompt();

    std::string input;
    getline(std::cin, input);

    return input;
}

void io_handler::write(const std::string& output)
{
    std::cout << output;
}

void io_handler::write_shell_prompt()
{
    std::string prompt =
            environment::get_current_user() +
            PROMPT_PREFIX +
            environment::get_current_working_directory() +
            ARROW;

    write(prompt);
}
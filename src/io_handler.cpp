#include <iostream>

#include "environment.h"
#include "io_handler.h"

#define NEW_LINE "\n"
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

void io_handler::write_line(const std::string& output)
{
    std::cout << output << NEW_LINE;
}

void io_handler::move_to_next_line()
{
    std::cout << NEW_LINE;
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
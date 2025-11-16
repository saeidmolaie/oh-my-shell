#include <iostream>

#include "environment/environment.h"
#include "io/io_handler.h"
#include "color.h"

#define NEW_LINE "\n"
#define PROMPT_PREFIX " at "
#define ARROW " ➜ "

std::string io_handler::read()
{
	write_shell_prompt();

	std::string input;

	getline(std::cin, input);
	write(color::RESET);

	std::cout.flush();
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
			color::GRUVBOX_BRIGHT_YELLOW +
			environment::get_current_user() +
			color::GRUVBOX_BRIGHT_CYAN +
			PROMPT_PREFIX +
			environment::get_current_working_directory() +
			ARROW +
			color::GRUVBOX_BRIGHT_YELLOW;

	write(prompt);
}
#include <string>

#include "banner.h"
#include "environment.h"
#include "builtin_prompts.h"
#include "path.h"
#include "prompt.h"
#include "io_handler.h"

static bool banner_printed = false;

int main()
{
	if (!banner_printed)
	{
		print_banner();
		banner_printed = true;
	}

	const path* const env_path = environment::get_path();

	std::string input;
	while (true)
	{
		input = io_handler::read();

		if (input.empty())
			continue;

		if (input == EXIT_PROMPT)
			break;

		prompt prompt(input);

		// If the prompt is a built-in command, process it and continue the loop.
		if (process_builtin_prompt(prompt))
			continue;

		const std::string& command = prompt.get_command();
		const std::string& command_path = env_path->get_path_to(command);
		const std::string& args = prompt.get_args();

		if (!command_path.empty())
		{
			std::string full_command;

			full_command += command_path;
			full_command += " ";
			full_command += args;

			std::system(full_command.c_str());

			continue;
		}

		std::string error_message =
				"command not found : " + command;

		io_handler::write_line(color::GRUVBOX_BRIGHT_RED + error_message);
	}

	return 0;
}
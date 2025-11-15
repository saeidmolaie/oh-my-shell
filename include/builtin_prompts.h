#pragma once

#include <unordered_map>
#include <functional>
#include <unistd.h>
#include <cstdlib>

#include "prompt.h"
#include "environment.h"

#define CHANGE_DIRECTORY_PROMPT "cd"
#define EXIT_PROMPT "exit"

static void handle_exit_prompt([[maybe_unused]] const prompt& prompt)
{
	exit(0);
}

static void handle_change_directory(const prompt& prompt)
{
	const std::string& args = prompt.get_args();
	const std::string& home_directory = environment::get_home_directory();

	if (args.empty())
	{
		if (chdir(home_directory.c_str()) != 0)
		{
			perror(CHANGE_DIRECTORY_PROMPT);
		}

		return;
	}

	std::string path = args;

	if (path == HOME_DIRECTORY_SYMBOL)
	{
		path = home_directory;
	}

	if (chdir(path.c_str()) != 0)
	{
		perror(CHANGE_DIRECTORY_PROMPT);
	}
}

static const std::unordered_map<std::string, std::function<void(const prompt& prompt)>>
		builtin_prompts_to_implementation_map =
		{
				{CHANGE_DIRECTORY_PROMPT, handle_change_directory},
				{EXIT_PROMPT,             handle_exit_prompt}
		};

bool process_builtin_prompt(const prompt& prompt)
{
	auto iterator =
			builtin_prompts_to_implementation_map.find(prompt.get_command());

	if (iterator == builtin_prompts_to_implementation_map.end())
		return false;

	const auto& action = iterator->second;
	action(prompt);

	return true;
}
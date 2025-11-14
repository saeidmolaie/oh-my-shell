#pragma once

#include <unordered_map>
#include <functional>
#include <unistd.h>
#include <cstdlib>

#include "prompt.h"
#include "environment.h"

#define CHANGE_DIRECTORY_PROMPT "cd"
#define EXIT_PROMPT "exit"

void handle_exit_prompt([[maybe_unused]] const prompt& prompt)
{
	exit(0);
}

void handle_change_directory(const prompt& prompt)
{
	const auto& args = prompt.get_args();

	if (args.empty())
	{
		chdir(environment::get_home_directory().c_str());
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
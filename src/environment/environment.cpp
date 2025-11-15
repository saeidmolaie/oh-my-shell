#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <cstring>
#include <string>
#include <cstdlib>

#include "environment/environment.h"

const path* const environment::get_path()
{
	static path* env_path = nullptr;

	if (env_path == nullptr)
	{
		env_path =
				new path(std::getenv("PATH"));
	}

	return env_path;
}

const std::string& environment::get_home_directory()
{
	static const std::string home_directory = std::getenv("HOME");
	return home_directory;
}

const size_t& environment::get_home_directory_length()
{
	static const std::size_t home_directory_length = get_home_directory().length() - 2;
	return home_directory_length;
}

const std::string& environment::get_current_user()
{
	static std::string user =
			getpwuid(getuid())->pw_name;

	return user;
}

const std::string& environment::get_current_working_directory()
{
	char buffer[PATH_MAX];

	static std::string current_working_directory;

	if (getcwd(buffer, sizeof(buffer)) != nullptr)
	{
		std::string full_path(buffer);

		if (full_path.compare(0, get_home_directory_length(), get_home_directory()) == 0)
		{
			current_working_directory =
					HOME_DIRECTORY_SYMBOL +
					full_path.substr(get_home_directory_length());

			return current_working_directory;
		}

		current_working_directory = std::move(full_path);
	}

	return current_working_directory;
}
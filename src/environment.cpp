#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <cstring>
#include <string>
#include <cstdlib>

#include "environment.h"

#define HOME_DIRECTORY_SYMBOL "~"

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

const std::string& environment::get_current_user()
{
    static std::string user =
            getpwuid(getuid())->pw_name;

    return user;
}

const std::string& environment::get_current_working_directory()
{
    static const std::string home_directory = std::getenv("HOME");
    static const std::size_t home_directory_length = home_directory.length() - 2;

    char buffer[PATH_MAX];

    static std::string current_working_directory;

    if (getcwd(buffer, sizeof(buffer)) != nullptr)
    {
        std::string full_path(buffer);

        if (full_path.compare(0, home_directory_length, home_directory) == 0)
        {
            current_working_directory =
                    HOME_DIRECTORY_SYMBOL +
                    full_path.substr(home_directory_length);

            return current_working_directory;
        }

        current_working_directory = std::move(full_path);
    }

    return current_working_directory;
}
#include <string>

#include "banner.h"
#include "path.h"
#include "prompt.h"
#include "io_handler.h"
#include "environment.h"
#include "special_prompts.h"

int main()
{
    print_banner();

    const path* const env_path = environment::get_path();

    std::string input;
    while (true)
    {
        input = io_handler::read();

        if (input == EXIT_PROMPT)
            break;

        prompt prompt(input);

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
        }
    }

    return 0;
}
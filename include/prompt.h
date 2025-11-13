#pragma once

#include <string>

struct prompt
{

private:
    std::string m_command;
    std::string m_args;

public:
    explicit prompt(const std::string& input)
    {
        parse(input);
    }

public:
    const std::string& get_command()
    {
        return m_command;
    }

    const std::string& get_args()
    {
        return m_args;
    }

private:
    void parse(const std::string& input)
    {
        std::string buffer;
        bool first_space = true;

        for (int i = 0; i < input.length(); i++)
        {
            const char& character = input.at(i);

            if (first_space && std::isspace(character))
            {
                first_space = false;
                m_command = std::move(buffer);

                continue;
            }

            buffer += character;
        }

        m_args = std::move(buffer);
    }
};
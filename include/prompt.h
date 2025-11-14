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
		const std::string& get_command() const
		{
			return m_command;
		}

		const std::string& get_args() const
		{
			return m_args;
		}

	private:
		void parse(const std::string& input)
		{
			std::string buffer;
			bool command_parsed = false;

			for (int i = 0; i < input.length(); i++)
			{
				const char& character = input.at(i);

				if (!command_parsed && std::isspace(character))
				{
					command_parsed = true;
					m_command = std::move(buffer);

					continue;
				}

				buffer += character;
			}

			if (!command_parsed)
			{
				m_command = std::move(buffer);
				return;
			}

			m_args = std::move(buffer);
		}
};
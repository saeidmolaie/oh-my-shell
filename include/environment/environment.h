#pragma once

#include <string>

#include "path.h"

#define HOME_DIRECTORY_SYMBOL "~"

class environment
{

	public:
		environment() = delete;
		environment(const environment&) = delete;
		environment& operator=(const environment&) = delete;

	public:
		static const path* const get_path();

	public:
		static const std::string& get_home_directory();
		static const size_t& get_home_directory_length();

	public:
		static const std::string& get_current_user();
		static const std::string& get_current_working_directory();

};
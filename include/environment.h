#pragma once

#include <string>

#include "path.h"

class environment
{

public:
    environment() = delete;
    environment(const environment&) = delete;
    environment& operator=(const environment&) = delete;

public:
    static const path* const get_path();
    static const std::string& get_current_user();
    static const std::string& get_current_working_directory();

};
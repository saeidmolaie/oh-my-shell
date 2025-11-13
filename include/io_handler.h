#pragma once

#include <string>

class io_handler
{

public:
    io_handler() = delete;
    io_handler(const io_handler&) = delete;
    io_handler& operator=(const io_handler&) = delete;

public:
    static std::string read();
    static void write(const std::string& output);

private:
    static void write_shell_prompt();

};
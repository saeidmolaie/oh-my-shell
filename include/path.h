#pragma once

#include <string>
#include <map>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <fstream>

struct path
{

private:
    std::map<std::string, std::string> m_command_to_path_map;

public:
    explicit path(const std::string& path)
    {
        parse(path);
    }

public:
    const std::string& get_path_to(const std::string& command)
    {
        static const std::string empty;

        auto it =
                m_command_to_path_map.find(command);

        if (it != m_command_to_path_map.end())
            return it->second;

        return empty;
    }

private:
    void parse(const std::string& path)
    {
        const char separator = ':';

        std::stringstream ss(path);
        std::string directory_path;

        while (std::getline(ss, directory_path, separator))
        {
            if (directory_path.empty())
                continue;

            std::filesystem::path directory(directory_path);

            if (!std::filesystem::exists(directory) ||
                !std::filesystem::is_directory(directory))
                continue;

            for (const auto& entry : std::filesystem::directory_iterator(directory))
            {
                if(is_executable_file(entry))
                {
                    std::string filename = entry.path().filename().string();
                    std::string full_path = entry.path().string();

                    m_command_to_path_map.emplace(filename, full_path);
                }
            }
        }
    }

    static bool is_executable_file(const std::filesystem::path& file)
    {
        std::ifstream in(file, std::ios::binary);

        if (!in)
            return false;

        unsigned char magic[4] = {0};

        in.read(reinterpret_cast<char*>(magic), 4);

        if (in.gcount() == 4 &&
            magic[0] == 0x7F &&
            magic[1] == 'E' &&
            magic[2] == 'L' &&
            magic[3] == 'F')
            return true;

        if (in.gcount() >= 2 &&
            magic[0] == '#' &&
            magic[1] == '!')
            return true;

        return false;
    }
};
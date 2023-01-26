#pragma once

#include <filesystem>

namespace Snowflake
{
    class FileSystem
    {
    public:
        static std::string ReadFile(const std::filesystem::path& Filepath);
    };
}
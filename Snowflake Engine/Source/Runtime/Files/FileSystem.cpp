#include "SnowflakePCH.h"
#include "FileSystem.h"

namespace Snowflake
{
    std::string FileSystem::ReadFile(const std::filesystem::path& Filepath)
    {
        std::string Result;
        std::ifstream FileReader(Filepath.string(), std::ios::in | std::ios::binary); // Closes automatically thanks to RAII.
        if (FileReader)
        {
            FileReader.seekg(0, std::ios::end);
            size_t Size = FileReader.tellg();
            if (Size != -1)
            {
                Result.resize(Size);
                FileReader.seekg(0, std::ios::beg);
                FileReader.read(&Result[0], Size);
            }
            else
            {
                ENGINE_LOG_ERROR_TAG("IO", "Failed to read file '{}'!", Filepath.string());
            }
        }
        else
        {
            ENGINE_LOG_ERROR_TAG("IO", "Failed to open file '{}'!", Filepath.string());
        }

        return Result;
    }
}

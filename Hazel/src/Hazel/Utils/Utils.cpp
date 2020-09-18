#include "pch.h"
#include "Utils.h"
#include <fstream>
#include <filesystem>

namespace Hazel
{
    namespace Utils
    {
        bool StringCmpCaseInsensitive(const std::string& a, const std::string& b)
        {
            if (a.size() != b.size())
            {
                return false;
            }

            return std::equal(a.begin(), a.end(), b.begin(), [](const char& c1, const char& c2)
                {
                    return std::tolower(c1) == std::tolower(c2);
                });
        }

        std::string LoadFile(const char* path)
        {
            std::ifstream ifs(path, std::ios::in);
            std::ostringstream ss;
            ss << ifs.rdbuf();
            return ss.str();
        }

        std::string GetFileNameWithExt(const char* path)
        {
            return std::filesystem::path(path).filename().string();
        }

        std::string GetFileNameWithoutExt(const char* path)
        {
            std::filesystem::path pathObj(path);
            if (pathObj.has_stem())
            {
                return pathObj.stem().string();
            }
            return std::string();
        }
    }
}
#pragma once

namespace Hazel
{
    namespace Utils
    {
        bool StringCmpCaseInsensitive(const std::string& first, const std::string& second);
        std::string LoadFile(const char* path);
        std::string GetFileNameWithExt(const char* path);
        std::string GetFileNameWithoutExt(const char* path);
    }
}
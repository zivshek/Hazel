#pragma once

namespace Hazel
{
    namespace Utils
    {
        bool StringCmpCaseInsensitive(const std::string& first, const std::string& second);
        std::string LoadFile(const char* file);
    }
}
#include "pch.h"
#include "Utils.h"

#include <fstream>

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

        std::string LoadFile(const char* file)
        {
            std::ifstream ifs(file, std::ios::in);
            std::ostringstream ss;
            ss << ifs.rdbuf();
            return ss.str();
        }
    }
}
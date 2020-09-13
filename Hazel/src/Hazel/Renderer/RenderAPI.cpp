#include "pch.h"
#include "RenderAPI.h"

namespace Hazel
{
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;
    Version RenderAPI::s_Version;
    Version RenderAPI::s_MinVersion{ 4, 5 };

    bool operator<(const Version& first, const Version& second)
    {
        if (first.Major < second.Major) return true;
        else if (first.Major > second.Major) return false;

        if (first.Minor < second.Minor) return true;
        else return false;
    }

    bool operator==(const Version& first, const Version& second)
    {
        return first.Major == second.Major && first.Minor == second.Minor;
    }

    bool operator>(const Version& first, const Version& second)
    {
        return !(first == second) && !(first < second);
    }

    bool operator>=(const Version& first, const Version& second)
    {
        return (first > second) || (first == second);
    }
}
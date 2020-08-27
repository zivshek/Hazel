#pragma once
#include "Hazel/Core.h"

namespace Hazel
{
    class Renderer
    {
    public:
        enum class API
        {
            OpenGL, None
        };

        inline static API GetAPI() { return s_API; }

    private:
        static API s_API;
    };
}
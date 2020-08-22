#pragma once

namespace Hazel
{
    typedef unsigned int uint;

#ifdef HZ_PLATFORM_WINDOWS
#include "GLFW/glfw3.h"
#define PlatformWindow GLFWwindow
#else
#define PlatformWindow void*
#endif
}
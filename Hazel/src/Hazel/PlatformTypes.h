#pragma once

namespace Hazel
{
    typedef unsigned int uint;

#ifdef USE_GLFW
#include "GLFW/glfw3.h"
#define PlatformWindow GLFWwindow
#else
#define PlatformWindow void*
#endif
}
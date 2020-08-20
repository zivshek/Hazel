#pragma once

namespace Hazel
{
#ifdef USE_GLFW
#include "GLFW/glfw3.h"
#define PlatformWindow GLFWwindow
#else
#define PlatformWindow void*
#endif
}
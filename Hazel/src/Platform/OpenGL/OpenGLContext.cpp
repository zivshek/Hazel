#include "pch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel
{
    OpenGLContext::OpenGLContext(GLFWwindow* window)
        : m_Window{ window }
    {
        HZ_CORE_ASSERT(m_Window, "GLFWwindow is invalid");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_Window);
        int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        HZ_CORE_ASSERT(result, "Initialize glad failed");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }
}
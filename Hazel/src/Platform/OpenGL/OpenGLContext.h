#pragma once
#include "Hazel/Core.h"

#include "Hazel/Rendering/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* window);

        void Init() override;

        void SwapBuffers() override;

    private:
        GLFWwindow* m_Window;
    };
}
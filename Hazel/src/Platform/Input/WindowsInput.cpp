#include "pch.h"
#include "WindowsInput.h"
#include "Hazel/Application.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
    std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

    bool WindowsInput::IsKeyPressed(int keycode) const
    {
        auto window = Application::Get().GetWindow().GetPlatformWindow();
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressed(int button) const
    {
        auto window = Application::Get().GetWindow().GetPlatformWindow();
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePosition() const
    {
        auto window = Application::Get().GetWindow().GetPlatformWindow();
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return std::make_pair((float)x, (float)y);
    }
}
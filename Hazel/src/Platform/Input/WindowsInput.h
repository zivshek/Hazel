#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/Input.h"

namespace Hazel
{
    class  WindowsInput : public Input
    {
    public:
        bool IsKeyPressed(int keycode) const override;

        bool IsMouseButtonPressed(int button) const override;

        glm::vec2 GetMousePosition() const override;
    };
}
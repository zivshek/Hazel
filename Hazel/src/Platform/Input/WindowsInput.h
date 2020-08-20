#pragma once

#include "Hazel/Core.h"
#include "Hazel/Input.h"

namespace Hazel
{
    class HAZEL_API WindowsInput : public Input
    {
    public:
        bool IsKeyPressed(int keycode) const override;

        bool IsMouseButtonPressed(int button) const override;

        std::pair<float, float> GetMousePosition() const override;
    };
}
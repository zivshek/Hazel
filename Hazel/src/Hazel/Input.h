#pragma once
#include "pch.h"
#include "Hazel/Core.h"

namespace Hazel
{
    class  Input
    {
    public:
        virtual ~Input() {}
        virtual bool IsKeyPressed(int keycode) const = 0;
        virtual bool IsMouseButtonPressed(int button) const = 0;
        // TODO: use vec2 when a math library is introduced
        virtual std::pair<float, float> GetMousePosition() const = 0;

        static Input& Get() { return *s_Instance; }
    private:
        static std::unique_ptr<Input> s_Instance;
    };
}
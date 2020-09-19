#pragma once
#include "pch.h"
#include "Hazel/Core/Core.h"
#include <glm/glm.hpp>

namespace Hazel
{
    class  Input
    {
    public:
        virtual ~Input() {}
        virtual bool IsKeyPressed(int keycode) const = 0;
        virtual bool IsMouseButtonPressed(int button) const = 0;
        virtual glm::vec2 GetMousePosition() const = 0;

        static Input& Get() { return *s_Instance; }
    private:
        static std::unique_ptr<Input> s_Instance;
    };
}

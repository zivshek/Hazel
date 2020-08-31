#pragma once

#include "Hazel/Core.h"
#include "Hazel/Core/Timestep.h"

namespace Hazel
{
    class Event;

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnUpdate(Timestep deltaTime) {}
        virtual void OnDraw() {}
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnEvent(Event& e) {}
        virtual void OnDrawImGui() {}

        inline const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
}
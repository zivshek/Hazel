#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
    class Event;

    class HAZEL_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnUpdate() {}
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnEvent(Event& e) {}

        inline const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
}
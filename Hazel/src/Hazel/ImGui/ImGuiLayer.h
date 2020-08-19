#pragma once

#include "Hazel/Layer.h"
#include "Hazel/Events/MouseEvents.h"
#include "Hazel/Events/KeyEvents.h"
#include "Hazel/Events/ApplicationEvents.h"

namespace Hazel
{
    class HAZEL_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnUpdate() override;
        void OnEvent(Event& e) override;
        void OnAttach() override;
        void OnDetach() override;
    private:
        bool OnMousePressed(MousePressedEvent& e);
        bool OnMouseReleased(MouseReleasedEvent& e);
        bool OnMouseMoved(MouseMovedEvent& e);
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnKeyReleased(KeyReleasedEvent& e);
        bool OnKeyTyped(KeyTypedEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

        float m_Time;
    };
}
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

        void OnAttach() override;
        void OnDetach() override;
        void DrawImGui() override;

        void Begin();
        void End();
    private:
        float m_Time;
    };
}
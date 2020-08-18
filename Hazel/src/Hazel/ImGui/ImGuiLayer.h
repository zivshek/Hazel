#pragma once

#include "Hazel/Layer.h"

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
        float m_Time;
    };
}
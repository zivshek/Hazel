#pragma once
#include <Hazel.h>

class Sandbox2D : public Hazel::Layer
{
public:
    Sandbox2D();
    ~Sandbox2D();

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Hazel::Timestep deltaTime) override;
    void OnDraw() override;
    void OnEvent(Hazel::Event& e) override;
    void OnDrawImGui() override;

private:
    Hazel::OrthoCameraController m_CameraController;
    Hazel::Ref<Hazel::VertexArray> m_VertexArray;

    glm::vec4 m_FlatColor;
};
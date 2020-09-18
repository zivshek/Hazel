#pragma once
#include "Hazel/Core.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Renderer/Camera.h"
#include "Hazel/Events/MouseEvents.h"
#include "Hazel/Events/ApplicationEvents.h"

namespace Hazel
{
    class OrthoCameraController
    {
    public:
        OrthoCameraController(float aspectRatio);
        ~OrthoCameraController();

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
        void UpdateCameraProjection();

    private:
        float m_AspectRatio;
        float m_Zoom;
        OrthographicCamera m_Camera;
        glm::vec3 m_CameraPosition;
        float m_CameraSpeed;
    };
}
#include "pch.h"
#include "OrthoCameraController.h"

#include "Hazel/Input.h"
#include "Hazel/InputCodes.h"

namespace Hazel
{
    const float c_defaultZoom = 2.0f;

    OrthoCameraController::OrthoCameraController(float aspectRatio)
        : m_AspectRatio(aspectRatio)
        , m_Zoom(c_defaultZoom)
        , m_Camera(-aspectRatio * c_defaultZoom, aspectRatio* c_defaultZoom, -c_defaultZoom, c_defaultZoom)
        , m_CameraPosition(0.f)
        , m_CameraSpeed(5.0f)
    {
    }

    OrthoCameraController::~OrthoCameraController()
    {
    }

    void OrthoCameraController::OnUpdate(Timestep ts)
    {
        if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_W))
            m_CameraPosition.y += m_CameraSpeed * ts;
        else if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_S))
            m_CameraPosition.y -= m_CameraSpeed * ts;

        if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_A))
            m_CameraPosition.x -= m_CameraSpeed * ts;
        else if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_D))
            m_CameraPosition.x += m_CameraSpeed * ts;

        m_Camera.SetPosition(m_CameraPosition);
        m_CameraSpeed = m_Zoom;
    }

    void OrthoCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthoCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthoCameraController::OnWindowResized));
    }

    bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_Zoom -= e.GetYOffset() * 0.25f;
        m_Zoom = std::max(m_Zoom, 0.25f);
        UpdateCameraProjection();
        return true;
    }

    bool OrthoCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        UpdateCameraProjection();
        return true;
    }

    void OrthoCameraController::UpdateCameraProjection()
    {
        m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    }
}
#include "pch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ProjMat{ glm::ortho(left, right, bottom, top, -1.0f, 1.0f) }
        , m_Position{}
        , m_Rotation{ 0 }
        , m_ViewMat{ 1.0f }
    {
        m_ViewProjMat = m_ProjMat * m_ViewMat;
    }

    void OrthographicCamera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        UpdateViewMatrix();
    }

    void OrthographicCamera::SetRotation(float rotation)
    {
        m_Rotation = rotation;
        UpdateViewMatrix();
    }

    void OrthographicCamera::UpdateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
        m_ViewMat = glm::inverse(transform);
        m_ViewProjMat = m_ProjMat * m_ViewMat;
    }
}
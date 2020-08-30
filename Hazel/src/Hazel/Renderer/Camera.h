#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position);

        float GetRotation() const { return m_Rotation; }
        void SetRotation(float rotation);

        const glm::mat4& GetProjMatrix() const { return m_ProjMat; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMat; }
        const glm::mat4& GetViewProjMatrix() const { return m_ViewProjMat; }

    private:
        void UpdateViewMatrix();

    private:
        glm::mat4 m_ProjMat;
        glm::mat4 m_ViewMat;
        glm::mat4 m_ViewProjMat;
        glm::vec3 m_Position;
        float m_Rotation;
    };
}
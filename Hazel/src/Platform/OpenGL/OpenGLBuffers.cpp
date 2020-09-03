#include "pch.h"
#include "OpenGLBuffers.h"
#include "Hazel/Renderer/RenderAPI.h"

#include <glad/glad.h>

namespace Hazel
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint size)
    {
        if (RenderAPI::GetVersion() < RenderAPI::GetMinVersion())
            glGenBuffers(1, &m_Id);
        else
            glCreateBuffers(1, &m_Id);

        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_Id);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //----------------------------------------------------------------

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint* indices, uint count)
        : m_Count{ count }
    {
        if (RenderAPI::GetVersion() < RenderAPI::GetMinVersion())
            glGenBuffers(1, &m_Id);
        else
            glCreateBuffers(1, &m_Id);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof uint, indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_Id);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
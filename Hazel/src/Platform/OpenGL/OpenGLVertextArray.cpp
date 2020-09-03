#include "pch.h"
#include "OpenGLVertexArray.h"
#include "Hazel/Renderer/RenderAPI.h"

#include <glad/glad.h>

namespace Hazel
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case Hazel::ShaderDataType::Float:    return GL_FLOAT;
        case Hazel::ShaderDataType::Float2:   return GL_FLOAT;
        case Hazel::ShaderDataType::Float3:   return GL_FLOAT;
        case Hazel::ShaderDataType::Float4:   return GL_FLOAT;
        case Hazel::ShaderDataType::Mat3:     return GL_FLOAT;
        case Hazel::ShaderDataType::Mat4:     return GL_FLOAT;
        case Hazel::ShaderDataType::Int:      return GL_INT;
        case Hazel::ShaderDataType::Int2:     return GL_INT;
        case Hazel::ShaderDataType::Int3:     return GL_INT;
        case Hazel::ShaderDataType::Int4:     return GL_INT;
        case Hazel::ShaderDataType::Bool:     return GL_BOOL;
        }

        HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        if (RenderAPI::GetVersion() < RenderAPI::GetMinVersion())
            glGenVertexArrays(1, &m_Id);
        else
            glCreateVertexArrays(1, &m_Id); // oops, my laptop doesn't support this
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_Id);
    }

    void OpenGLVertexArray::Bind()
    {
        glBindVertexArray(m_Id);
    }

    void OpenGLVertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertextBuffer)
    {
        HZ_CORE_ASSERT(vertextBuffer->GetLayout().GetElements().size(), "Must set layout first");

        glBindVertexArray(m_Id);
        vertextBuffer->Bind();

        uint i = 0;
        const auto& layout = vertextBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,
                ShaderDataTypeCount(element.Type),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized,
                layout.GetStride(),
                (const void*)element.Offset);
            i++;
        }
        m_VertexBuffers.push_back(vertextBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_Id);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    }
}
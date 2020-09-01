#include "pch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Hazel
{
    OpenGLTexture2D::OpenGLTexture2D(const char* path)
        : m_Id{ 0 }
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        auto data = stbi_load(path, &width, &height, &channels, 0);
        HZ_CORE_ASSERT(data, "Failed to load image at {0}", path);
        m_Width = (uint)width;
        m_Height = (uint)height;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
        glTextureStorage2D(m_Id, 1, GL_RGB8, width, height);
        glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureSubImage2D(m_Id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_Id);
    }

    void OpenGLTexture2D::Bind(uint slot /*= 0*/) const
    {
        glBindTextureUnit(slot, m_Id);
    }
}
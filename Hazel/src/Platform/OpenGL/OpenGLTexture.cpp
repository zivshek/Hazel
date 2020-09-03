#include "pch.h"
#include "OpenGLTexture.h"
#include "Hazel/Renderer/RenderAPI.h"

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

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        HZ_CORE_ASSERT(internalFormat && dataFormat, "Image format not supported.");

        if (RenderAPI::GetVersion() < RenderAPI::GetMinVersion())
        {
            glGenTextures(1, &m_Id);
            Bind();
            glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, width, height);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
            glTextureStorage2D(m_Id, 1, internalFormat, width, height);
            glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureSubImage2D(m_Id, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
        }
        
        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_Id);
    }

    void OpenGLTexture2D::Bind(uint slot /*= 0*/) const
    {
        if (RenderAPI::GetVersion() < RenderAPI::GetMinVersion())
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, m_Id);
        }
        else
            glBindTextureUnit(slot, m_Id);
        
    }
}
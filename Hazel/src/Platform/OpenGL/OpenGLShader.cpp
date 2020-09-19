#include "pch.h"
#include "OpenGLShader.h"

#include "Hazel/Utils/Utils.h"
#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

namespace Hazel
{
    static GLenum GetShaderType(const std::string& type)
    {
        if (Utils::StringCmpCaseInsensitive(type, "vertex"))
        {
            return GL_VERTEX_SHADER;
        }
        if (Utils::StringCmpCaseInsensitive(type, "fragment") || Utils::StringCmpCaseInsensitive(type, "pixel"))
        {
            return GL_FRAGMENT_SHADER;
        }
        HZ_CORE_ASSERT(false, "Unsupported shader type");
        return 0;
    }

    static const std::string s_WhiteSpace = " \t";

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& file)
        : m_Program{ 0 }
    {
        m_Name = name;
        Process(file);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_Program);
    }

    void OpenGLShader::Bind()
    {
        glUseProgram(m_Program);
    }

    void OpenGLShader::Unbind()
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetUniformInt(const std::string& uniform, const int i)
    {
        GLint loc = glGetUniformLocation(m_Program, uniform.c_str());
        if (loc != -1)
        {
            glUniform1i(loc, i);
        }
    }

    void OpenGLShader::Process(const std::string& file)
    {
        std::string source = Utils::LoadFile(file.c_str());
        std::unordered_map<GLenum, std::string> shaderSourceMap;

        std::string typeToken = "#type";
        uint searchStart = 0;
        size_t pos = std::string::npos;
        do
        {
            pos = source.find(typeToken, searchStart);
            size_t eol = source.find_first_of("\r\n", pos);
            size_t start = source.find_first_not_of(s_WhiteSpace, pos + strlen(typeToken.c_str()));
            auto typeStr = source.substr(start, eol - start);
            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            searchStart = pos;
            shaderSourceMap[GetShaderType(typeStr)] = source.substr(nextLinePos, pos == std::string::npos ? source.size() - nextLinePos : pos - nextLinePos);
        } while (pos != std::string::npos);

        m_Program = glCreateProgram();
        HZ_CORE_ASSERT(shaderSourceMap.size() <= 2, "We only support 2 shaders for now");
        std::array<GLuint, 2> shaders;
        int index = 0;
        for (const auto& pair : shaderSourceMap)
        {
            GLuint shader = glCreateShader(pair.first);
            const GLchar* source = (const GLchar*)pair.second.c_str();
            glShaderSource(shader, 1, &source, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                HZ_CORE_ERROR("Shader compile error {1}", infoLog.data());
                break;
            }
            shaders[index++] = shader;
            glAttachShader(m_Program, shader);
        }

        glLinkProgram(m_Program);

        GLint isLinked = 0;
        glGetProgramiv(m_Program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_Program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(m_Program);
            // Don't leak shaders either.
            for (const auto shader : shaders)
            {
                glDeleteShader(shader);
            }

            // Use the infoLog as you see fit.
            HZ_CORE_ERROR("Shader program link error {0}", infoLog.data());
            // In this simple program, we'll just leave
            return;
        }

        // Always detach shaders after a successful link.
        for (const auto shader : shaders)
        {
            glDetachShader(m_Program, shader);
        }
    }

    void OpenGLShader::SetUniformMat4(const std::string& uniform, const glm::mat4& mat)
    {
        GLint loc = glGetUniformLocation(m_Program, uniform.c_str());
        if (loc != -1)
        {
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
        }
    }

    void OpenGLShader::SetUniformVec3(const std::string& uniform, const glm::vec3& vec)
    {
        GLint loc = glGetUniformLocation(m_Program, uniform.c_str());
        if (loc != -1)
        {
            glUniform3fv(loc, 1, glm::value_ptr(vec));
        }
    }

    void OpenGLShader::SetUniformVec4(const std::string& uniform, const glm::vec4& vec)
    {
        GLint loc = glGetUniformLocation(m_Program, uniform.c_str());
        if (loc != -1)
        {
            glUniform4fv(loc, 1, glm::value_ptr(vec));
        }
    }
}
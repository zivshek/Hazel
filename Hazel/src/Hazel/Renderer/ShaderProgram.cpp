#include "pch.h"
#include "ShaderProgram.h"

#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>

namespace Hazel
{
    ShaderProgram::ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
    {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar* source = (const GLchar*)vertexSource.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            HZ_CORE_ERROR("Vertex shader compile error {0}", infoLog.data());
            // In this simple program, we'll just leave
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = (const GLchar*)fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            HZ_CORE_ERROR("Fragment shader compile error {0}", infoLog.data());
            // In this simple program, we'll just leave
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_Program = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_Program, vertexShader);
        glAttachShader(m_Program, fragmentShader);

        // Link our program
        glLinkProgram(m_Program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
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
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            // Use the infoLog as you see fit.
            HZ_CORE_ERROR("Shader program link error {0}", infoLog.data());
            // In this simple program, we'll just leave
            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_Program, vertexShader);
        glDetachShader(m_Program, fragmentShader);
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_Program);
    }

    void ShaderProgram::Bind()
    {
        glUseProgram(m_Program);
    }

    void ShaderProgram::Unbind()
    {
        glUseProgram(0);
    }

    void ShaderProgram::SetUniform(const std::string uniform, const glm::mat4& mat)
    {
        GLint loc = glGetUniformLocation(m_Program, uniform.c_str());
        if (loc != -1)
        {
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
        }
    }
}
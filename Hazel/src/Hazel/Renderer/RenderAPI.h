#pragma once
#include "Hazel/Core.h"

#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Hazel
{
    struct Version
    {
        uint Major = -1;
        uint Minor = -1;

        Version(uint major, uint minor) : Major{ major }, Minor{ minor } {}
        Version() {}

        bool IsValid() const { return Major != -1; }
    };

    bool operator<(const Version& first, const Version& second);

    bool operator==(const Version& first, const Version& second);

    bool operator>(const Version& first, const Version& second);

    class RenderAPI
    {
    public:
        enum class API
        {
            OpenGL, None
        };

        virtual void Init() = 0;
        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        static API GetAPI() { return s_API; }
        static const Version& GetMinVersion() { return s_MinVersion; }
        static const Version& GetVersion() { return s_Version; }
        static void SetVersion(const Version& version) { s_Version = version; }
    private:
        static API s_API;
        static Version s_Version;
        static Version s_MinVersion;
    };
}
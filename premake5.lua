workspace "Hazel"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDirs["glad"] = "Hazel/vendor/glad/include"
IncludeDirs["imgui"] = "Hazel/vendor/imgui"
IncludeDirs["glm"] = "Hazel/vendor/glm"
IncludeDirs["stb_image"] = "Hazel/vendor/stb_image"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/glad"
include "Hazel/vendor/imgui"

project "Hazel"
    location "Hazel"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")
    pchheader "pch.h"
    pchsource "Hazel/src/pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.glad}",
        "%{IncludeDirs.imgui}",
        "%{IncludeDirs.glm}",
        "%{IncludeDirs.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib",
        "ImGui"
    }

    filter "system:Windows"
        systemversion "latest"

        defines
        {
            "HZ_PLATFORM_WINDOWS", "GLFW_INCLUDE_NONE", "HZ_ENABLE_ASSERT"
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "HZ_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Hazel/vendor/spdlog/include",
        "Hazel/src",
        "%{IncludeDirs.imgui}",
        "%{IncludeDirs.glm}"
    }

    links
    {
        "Hazel"
    }

    filter "system:Windows"
        systemversion "latest"
        defines
        {
            "HZ_PLATFORM_WINDOWS", "HZ_ENABLE_ASSERT"
        }
        
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "HZ_DIST"
        runtime "Release"
        optimize "on"
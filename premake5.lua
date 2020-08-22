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

include "Hazel/vendor/GLFW"
include "Hazel/vendor/glad"
include "Hazel/vendor/imgui"

project "Hazel"
    location "Hazel"
    kind "SharedLib"
    language "C++"
    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")
    pchheader "pch.h"
    pchsource "Hazel/src/pch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.glad}",
        "%{IncludeDirs.imgui}",
        "%{IncludeDirs.glm}"
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
        cppdialect "C++17"
        staticruntime "On"
        defines
        {
            "HZ_PLATFORM_WINDOWS", "HZ_BUILD_DLL", "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"
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
        "Hazel/vendor",
        "%{IncludeDirs.glm}"
    }

    links
    {
        "Hazel"
    }

    filter "system:Windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"
        defines
        {
            "HZ_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "HZ_DEBUG"        
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "DIST"
        runtime "Release"
        optimize "On"
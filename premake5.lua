workspace "Hazel"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["GLFW"] = "Hazel/vendor/GLFW/include"

include "Hazel/vendor/GLFW"

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
        "%{IncludeDirs.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:Windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"
        defines
        {
            "HZ_PLATFORM_WINDOWS", "HZ_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
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
        "Hazel/src"
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
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "DIST"
        buildoptions "/MD"
        optimize "On"
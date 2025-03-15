workspace "Tourqe"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Tourqe/vendor/glfw/include"

include "Tourqe/vendor/glfw"

project "Tourqe"
    location "Tourqe"
    kind "SharedLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "tupch.h"
    pchsource "Tourqe/src/tupch.cpp"
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

    includedirs 
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        buildoptions "/utf-8"

        defines 
        {
            "TU_PLATFORM_WINDOWS",
            "TU_BUILD_DLL",
            "TU_ENABLE_ASSERTS"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
        
    filter "configurations:Debug"
        defines "TU_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TU_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "TU_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Tourqe/vendor/spdlog/include",
        "Tourqe/src"
    }

    links 
    {
        "Tourqe"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        buildoptions "/utf-8"

        defines 
        {
            "TU_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "TU_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TU_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "TU_DIST"
        optimize "On"


workspace "Tourqe"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Tourqe/vendor/glfw/include"
IncludeDir["GLAD"] = "Tourqe/vendor/glad/include"
IncludeDir["ImGui"] = "Tourqe/vendor/ImGui/"
IncludeDir["glm"] = "Tourqe/vendor/glm/"

group "Dependencies"
    include "Tourqe/vendor/glfw"
    include "Tourqe/vendor/glad"
    include "Tourqe/vendor/imgui"
group ""

project "Tourqe"
    location "Tourqe"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "tupch.h"
    pchsource "Tourqe/src/tupch.cpp"
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines 
    {
        "_CRT_SECURE_NO_WARNINGS"
    }
    
    includedirs 
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        buildoptions "/utf-8"

        defines 
        {
            "TU_PLATFORM_WINDOWS",
            "TU_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
        
    filter "configurations:Debug"
        defines "TU_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TU_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "TU_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Tourqe/src",
        "Tourqe/vendor",
        "%{IncludeDir.glm}"
    }

    links 
    {
        "Tourqe"
    }

    filter "system:windows"
        systemversion "latest"
        buildoptions "/utf-8"

        defines 
        {
            "TU_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "TU_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TU_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "TU_DIST"
        runtime "Release"
        optimize "on"


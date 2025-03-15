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
IncludeDir["GLAD"] = "Tourqe/vendor/glad/include"
IncludeDir["ImGui"] = "Tourqe/vendor/ImGui/"

group "Dependencies"
    include "Tourqe/vendor/glfw"
    include "Tourqe/vendor/glad"
    include "Tourqe/vendor/imgui"
group ""

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
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
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
        
    filter "configurations:Debug"
        defines "TU_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "TU_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "TU_DIST"
        buildoptions "/MD"
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


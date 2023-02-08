include "Dependencies.lua"

workspace "Snowflake Engine"
    architecture "x86_64"
    startproject "Snowflake Editor"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

    flags
    {
        "MultiProcessorCompile"
    }

BinariesDir = "%{wks.location}/Binaries/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IntermediateDir = "!%{wks.location}/Intermediate/%{prj.name}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "Snowflake Engine/ThirdParty/GLFW"
    include "Snowflake Engine/ThirdParty/Glad"
    include "Snowflake Engine/ThirdParty/ImGui"
group ""

group "Core"
    project "Snowflake Engine"
        location "Snowflake Engine"
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "Off"

        targetname("SnowflakeEngine")

        targetdir(BinariesDir)
        objdir(IntermediateDir)

        pchsource "Snowflake Engine/Source/SnowflakePCH.cpp"
        pchheader "SnowflakePCH.h"

        files
        {
            "%{prj.name}/Source/**.cpp",
            "%{prj.name}/Source/**.h",
            
            "%{IncludeDir.stb_image}/*.cpp",
            "%{IncludeDir.stb_image}/*.h"
        }

        includedirs
        {
            "%{prj.name}/Source",
            "%{prj.name}/Source/Runtime",
            "%{prj.name}/Source/Runtime/GameCore",
            
            "%{IncludeDir.spdlog}",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.glm}",
            "%{IncludeDir.ImGui}",
            "%{IncludeDir.stb_image}"
        }

        links
        {
            "GLFW",
            "Glad",
            "ImGui",
            
            "opengl32.lib"
        }

        defines
        {
            "GLFW_INCLUDE_NONE"
        }

        filter "system:windows"
            systemversion "latest"
            
            defines
            {
                "SNOWFLAKE_PLATFORM_WIN64",
                "SNOWFLAKE_BUILD_DLL"
            }

        filter "configurations:Debug"
            symbols "On"

            defines
            {
                "SNOWFLAKE_BUILD_DEBUG"
            }

        filter "configurations:Release"
            optimize "On"

            defines
            {
                "SNOWFLAKE_BUILD_RELEASE"
            }

        filter "configurations:Distribution"
            optimize "On"
            symbols "Off"

            defines
            {
                "SNOWFLAKE_BUILD_DIST"
            }
group ""

group "Tools"
    project "Snowflake Editor"
        location "Snowflake Editor"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "Off"

        targetname("SnowflakeEditor")

        targetdir(BinariesDir)
        objdir(IntermediateDir)

        files
        {
            "%{prj.name}/Source/**.cpp",
            "%{prj.name}/Source/**.h"
        }

        includedirs
        {
            "%{prj.name}/Source",
            
            "Snowflake Engine/Source",
            "Snowflake Engine/Source/Runtime",
            
            "%{IncludeDir.spdlog}",
            "%{IncludeDir.ImGui}",
            "%{IncludeDir.glm}"
        }

        links
        {
            "Snowflake Engine"
        }
        
        filter "system:windows"
            systemversion "latest"
            
            defines
            {
                "SNOWFLAKE_PLATFORM_WIN64"
            }
        
        filter "configurations:Debug"
            symbols "On"
            
            defines
            {
                "SNOWFLAKE_BUILD_DEBUG"
            }
        
        filter "configurations:Release"
            optimize "On"
            
            defines
            {
                "SNOWFLAKE_BUILD_RELEASE"
            }
        
        filter "configurations:Distribution"
            optimize "On"
            symbols "Off"
            
            defines
            {
                "SNOWFLAKE_BUILD_DIST"
            }
group ""
project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir(BinariesDir)
    objdir(IntermediateDir)

    files
    {
        "*.cpp",
        "*.h",
        
        "backends/imgui_impl_glfw.cpp",
        "backends/imgui_impl_glfw.h",
        
        "backends/imgui_impl_opengl3.cpp",
        "backends/imgui_impl_opengl3.h",
        "backends/imgui_impl_opengl3_loader.h"
    }

    includedirs
    {
        "%{prj.location}",
        
        "backends",
        
        "%{IncludeDir.GLFW}"
    }

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        systemversion "latest"
        pic "On"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter "configurations:Distribution"
        runtime "Release"
        optimize "On"
        symbols "Off"
    
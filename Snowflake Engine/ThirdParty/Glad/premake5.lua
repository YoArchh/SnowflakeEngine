project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "off"
    
    targetdir(BinariesDir)
    objdir(IntermediateDir)

    files
    {
        "src/glad.c",
        
        "include/glad/glad.h",
        "include/KHR/khrplatform.h"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
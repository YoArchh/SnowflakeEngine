project "GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "Off"
    
    targetdir(BinariesDir)
    objdir(IntermediateDir)
    
    files
    {
        "src/context.c",
        "src/init.c",
        "src/input.c",
        "src/internal.h",
        "src/mappings.h",
        "src/monitor.c",
        
        "src/osmesa_context.c",
        "src/osmesa_context.h",
        
        "src/vulkan.c",
        "src/window.c",
        
        "include/**.h"
    }

    filter "system:windows"
        systemversion "latest"

        files
        {
            "src/egl_context.c",
            "src/egl_context.h",
            
            "src/wgl_context.c",
            "src/wgl_context.h",
            
            "src/win32_init.c",
            "src/win32_joystick.c",
            "src/win32_joystick.h",
            "src/win32_monitor.c",
            "src/win32_platform.h",
            "src/win32_thread.c",
            "src/win32_time.c",
            "src/win32_window.c",
        }

        defines
        {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "system:macosx"
        files
        {
            "src/cocoa_init.m",
            "src/cocoa_joystick.h",
            "src/cocoa_joystick.m",
            "src/cocoa_monitor.m",
            "src/cocoa_platform.h",
            "src/cocoa_time.c",
            "src/cocoa_window.m",
            
            "src/nsgl_context.m",
            "src/nsgl_context.h"
        }

        defines
        {
            "_GLFW_COCOA"
        }
    
    filter "system:linux"
        systemversion "latest"
        pic "On"

        files
        {
            "src/glx_context.c",
            "src/glx_context.h",
            
            "src/linux_joystick.c",
            "src/linux_joystick.h",
            
            "src/posix_time.c",
            "src/posix_time.h",
            
            "src/x11_init.c",
            "src/x11_monitor.c",
            "src/x11_platform.h",
            "src/x11_window.c",
            
            "src/xkb_unicode.c",
            "src/xkb_unicode.h",
        }

        defines
        {
            "_GLFW_X11"
        }

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
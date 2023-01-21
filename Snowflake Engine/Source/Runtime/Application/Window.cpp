#include "SnowflakePCH.h"
#include "Window.h"

#ifdef SNOWFLAKE_PLATFORM_WIN64
    #include "Windows/WindowsWindow.h"
#endif

namespace Snowflake
{
    Scope<Window> Window::CreateWindow(const WindowSpecification& Specification)
    {
        #ifdef SNOWFLAKE_PLATFORM_WIN64
            return CreateScope<WindowsWindow>(Specification);
        #else
            ENGINE_ASSERT(false, "Failed to create window '" + Specification.Title + "'! Unknown platform!");
            return nullptr;
        #endif
    }
}

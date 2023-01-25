#include "SnowflakePCH.h"
#include "Input.h"

#ifdef SNOWFLAKE_PLATFORM_WIN64
    #include "Windows/WindowsInput.h"
#endif

namespace Snowflake
{
    Input* Input::s_Instance = nullptr;
    
    void Input::Initialize()
    {
        #ifdef SNOWFLAKE_PLATFORM_WIN64
            s_Instance = new WindowsInput();
        #else
            ENGINE_ASSERT(false, "Failed to initialize Input! Unknown platform!");
            s_Instance = nullptr;
        #endif
    }
}
#pragma once

#ifdef SNOWFLAKE_PLATFORM_WIN64
    #ifdef SNOWFLAKE_BUILD_DLL
        #define SNOWFLAKE_API __declspec(dllexport)
    #else
        #define SNOWFLAKE_API __declspec(dllimport)
    #endif
#endif
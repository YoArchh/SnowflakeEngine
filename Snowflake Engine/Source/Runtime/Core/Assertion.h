#pragma once

#include "Logging/Logger.h"

#ifdef SNOWFLAKE_PLATFORM_WIN64
    #define SNOWFLAKE_DEBUG_BREAK __debugbreak()
#else
    #define SNOWFLAKE_DEBUG_BREAK
#endif

#ifdef SNOWFLAKE_BUILD_DEBUG
    #define SNOWFLAKE_ENABLE_ASSERTS
#endif

#define SNOWFLAKE_ENABLE_VERIFY

#ifdef SNOWFLAKE_ENABLE_ASSERTS
    #define ENGINE_ASSERT_MESSAGE_INTERNAL(...)  ::Snowflake::Logger::PrintAssertMessage(true, "Assertion Failed", __VA_ARGS__)
    #define CLIENT_ASSERT_MESSAGE_INTERNAL(...)  ::Snowflake::Logger::PrintAssertMessage(false, "Assertion Failed", __VA_ARGS__)

    #define ENGINE_ASSERT(Condition, ...) { if(!(Condition)) { ENGINE_ASSERT_MESSAGE_INTERNAL(__VA_ARGS__); SNOWFLAKE_DEBUG_BREAK; } }
    #define CLIENT_ASSERT(Condition, ...) { if(!(Condition)) { CLIENT_ASSERT_MESSAGE_INTERNAL(__VA_ARGS__); SNOWFLAKE_DEBUG_BREAK; } }
#else
    #define ENGINE_ASSERT(Condition, ...)
    #define CLIENT_ASSERT(Condition, ...)
#endif

#ifdef SNOWFLAKE_ENABLE_VERIFY
    #define ENGINE_VERIFY_MESSAGE_INTERNAL(...)  ::Snowflake::Logger::PrintAssertMessage(true, "Verify Failed", __VA_ARGS__)
    #define CLIENT_VERIFY_MESSAGE_INTERNAL(...)  ::Snowflake::Logger::PrintAssertMessage(false, "Verify Failed", __VA_ARGS__)

    #define ENGINE_VERIFY(Condition, ...) { if(!(Condition)) { ENGINE_VERIFY_MESSAGE_INTERNAL(__VA_ARGS__); SNOWFLAKE_DEBUG_BREAK; } }
    #define CLIENT_VERIFY(Condition, ...) { if(!(Condition)) { CLIENT_VERIFY_MESSAGE_INTERNAL(__VA_ARGS__); SNOWFLAKE_DEBUG_BREAK; } }
#else
    #define ENGINE_VERIFY(Condition, ...)
    #define CLIENT_VERIFY(Condition, ...)
#endif
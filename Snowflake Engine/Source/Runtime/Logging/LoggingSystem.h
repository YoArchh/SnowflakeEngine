#pragma once

#include "Core/CoreTypes.h"

namespace spdlog
{
    class logger;
}

namespace Snowflake
{
    class LoggingSystem
    {
    public:
        static Ref<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
        static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static void Initialize();
        static void Shutdown();

    private:
        static Ref<spdlog::logger> s_EngineLogger;
        static Ref<spdlog::logger> s_ClientLogger;
        
        friend class Application;
    };
}

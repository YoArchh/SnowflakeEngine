#include "SnowflakePCH.h"
#include "LoggingSystem.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Snowflake
{
    Ref<spdlog::logger> LoggingSystem::s_EngineLogger = nullptr;
    Ref<spdlog::logger> LoggingSystem::s_ClientLogger = nullptr;
    
    void LoggingSystem::Initialize()
    {
        std::vector<spdlog::sink_ptr> EngineLoggerSinks =
        {
            CreateRef<spdlog::sinks::basic_file_sink_mt>("Logs/Snowflake Engine.log", true),
            CreateRef<spdlog::sinks::stdout_color_sink_mt>()
        };

        std::vector<spdlog::sink_ptr> ClientLoggerSinks =
        {
            CreateRef<spdlog::sinks::basic_file_sink_mt>("Logs/Snowflake Client.log", true),
            CreateRef<spdlog::sinks::stdout_color_sink_mt>()
        };

        EngineLoggerSinks[0]->set_pattern("[%I:%M:%S] [%l] (%n): %v");
        EngineLoggerSinks[1]->set_pattern("[%I:%M:%S] %^[%l] (%n): %v%$");

        ClientLoggerSinks[0]->set_pattern("[%I:%M:%S] [%l] (%n): %v");
        ClientLoggerSinks[1]->set_pattern("[%I:%M:%S] %^[%l] (%n): %v%$");

        s_EngineLogger = CreateRef<spdlog::logger>("Snowflake Engine", EngineLoggerSinks.begin(), EngineLoggerSinks.end());
        s_EngineLogger->set_level(spdlog::level::trace);

        s_ClientLogger = CreateRef<spdlog::logger>("Snowflake Client", ClientLoggerSinks.begin(), ClientLoggerSinks.end());
        s_ClientLogger->set_level(spdlog::level::trace);
    }

    void LoggingSystem::Shutdown()
    {
        s_EngineLogger.reset();
        s_ClientLogger.reset();

        spdlog::drop_all();
    }
}

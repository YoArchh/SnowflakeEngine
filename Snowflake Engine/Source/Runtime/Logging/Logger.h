#pragma once

#include "Core/CoreTypes.h"

#include "LoggingSystem.h"

#include <spdlog/logger.h>

namespace Snowflake
{
    enum class LogLevel
    {
        Trace = 0,
        Info = 2,
        Debug = 1,
        Warn = 3,
        Error = 4,
        Critical = 5
    };
    
    class Logger
    {
    public:
        Logger(const std::string& Name);
        ~Logger();

        template<typename ... Args>
        static void PrintMessage(bool bLoggingFromEngine, LogLevel InLogLevel, Args&& ... Arguments);

        template<typename ... Args>
        static void PrintMessageWithTag(bool bLoggingFromEngine, LogLevel InLogLevel, std::string_view Tag, Args&& ... Arguments);

        template<typename ... Args>
        static void PrintAssertMessage(bool bLoggingFromEngine, std::string_view Prefix, Args&& ... Arguments);
    private:
        Ref<spdlog::logger> m_Logger;
        
        std::string m_Name;
    };
}

namespace Snowflake
{
    template <typename ... Args>
    void Logger::PrintMessage(bool bLoggingFromEngine, LogLevel InLogLevel, Args&&... Arguments)
    {
        auto Logger = bLoggingFromEngine ? LoggingSystem::GetEngineLogger() : LoggingSystem::GetClientLogger();

        switch (InLogLevel)
        {
            case LogLevel::Trace:
            {
                Logger->trace("{0}", fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Info:
            {
                Logger->info("{0}", fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Debug:
            {
                Logger->debug("{0}", fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Warn:
            {
                Logger->warn("{0}", fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Error:
            {
                Logger->error("{0}", fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Critical:
            {
                Logger->critical("{0}", fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
        }
    }

    template <typename ... Args>
    void Logger::PrintMessageWithTag(bool bLoggingFromEngine, LogLevel InLogLevel, std::string_view Tag, Args&&... Arguments)
    {
        auto Logger = bLoggingFromEngine ? LoggingSystem::GetEngineLogger() : LoggingSystem::GetClientLogger();
        auto LogString = Tag.empty() ? "{0}{1}" : "[{0}] {1}";

        switch (InLogLevel)
        {
            case LogLevel::Trace:
            {
                Logger->trace(LogString, Tag, fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Info:
            {
                Logger->info(LogString, Tag, fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Debug:
            {
                Logger->debug(LogString, Tag, fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Warn:
            {
                Logger->warn(LogString, Tag, fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Error:
            {
                Logger->error(LogString, Tag, fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
            case LogLevel::Critical:
            {
                Logger->critical(LogString, Tag, fmt::format(std::forward<Args>(Arguments)...));
                break;
            }
        }
    }

    template <typename ... Args>
    void Logger::PrintAssertMessage(bool bLoggingFromEngine, std::string_view Prefix, Args&&... Arguments)
    {
        auto Logger = bLoggingFromEngine ? LoggingSystem::GetEngineLogger() : LoggingSystem::GetClientLogger();
        Logger->error("{0}: {1}", Prefix, fmt::format(std::forward<Args>(Arguments)...));
    }

    template <>
    inline void Logger::PrintAssertMessage(bool bLoggingFromEngine, std::string_view Prefix)
    {
        auto Logger = bLoggingFromEngine ? LoggingSystem::GetEngineLogger() : LoggingSystem::GetClientLogger();
        Logger->error("{0}", Prefix);
    }
}

/* -- Engine Logging Macros -- */

#define ENGINE_LOG_TRACE(...)    Snowflake::Logger::PrintMessage(true, LogLevel::Trace, __VA_ARGS__)
#define ENGINE_LOG_INFO(...)     Snowflake::Logger::PrintMessage(true, LogLevel::Info, __VA_ARGS__)
#define ENGINE_LOG_DEBUG(...)    Snowflake::Logger::PrintMessage(true, LogLevel::Debug, __VA_ARGS__)
#define ENGINE_LOG_WARN(...)     Snowflake::Logger::PrintMessage(true, LogLevel::Warn, __VA_ARGS__)
#define ENGINE_LOG_ERROR(...)    Snowflake::Logger::PrintMessage(true, LogLevel::Error, __VA_ARGS__)
#define ENGINE_LOG_CRITICAL(...) Snowflake::Logger::PrintMessage(true, LogLevel::Critical, __VA_ARGS__)

#define ENGINE_LOG_TRACE_TAG(Tag, ...)    Snowflake::Logger::PrintMessageWithTag(true, LogLevel::Trace, Tag, __VA_ARGS__)
#define ENGINE_LOG_INFO_TAG(Tag, ...)     Snowflake::Logger::PrintMessageWithTag(true, LogLevel::Info, Tag, __VA_ARGS__)
#define ENGINE_LOG_DEBUG_TAG(Tag, ...)    Snowflake::Logger::PrintMessageWithTag(true, LogLevel::Debug, Tag, __VA_ARGS__)
#define ENGINE_LOG_WARN_TAG(Tag, ...)     Snowflake::Logger::PrintMessageWithTag(true, LogLevel::Warn, Tag, __VA_ARGS__)
#define ENGINE_LOG_ERROR_TAG(Tag, ...)    Snowflake::Logger::PrintMessageWithTag(true, LogLevel::Error, Tag, __VA_ARGS__)
#define ENGINE_LOG_CRITICAL_TAG(Tag, ...) Snowflake::Logger::PrintMessageWithTag(true, LogLevel::Critical, Tag, __VA_ARGS__)

/* -- Client Logging Macros -- */

#define CLIENT_LOG_TRACE(...)    Snowflake::Logger::PrintMessage(false, LogLevel::Trace, __VA_ARGS__)
#define CLIENT_LOG_INFO(...)     Snowflake::Logger::PrintMessage(false, LogLevel::Info, __VA_ARGS__)
#define CLIENT_LOG_DEBUG(...)    Snowflake::Logger::PrintMessage(false, LogLevel::Debug, __VA_ARGS__)
#define CLIENT_LOG_WARN(...)     Snowflake::Logger::PrintMessage(false, LogLevel::Warn, __VA_ARGS__)
#define CLIENT_LOG_ERROR(...)    Snowflake::Logger::PrintMessage(false, LogLevel::Error, __VA_ARGS__)
#define CLIENT_LOG_CRITICAL(...) Snowflake::Logger::PrintMessage(false, LogLevel::Critical, __VA_ARGS__)

#define CLIENT_LOG_TRACE_TAG(Tag, ...)    Snowflake::Logger::PrintMessageWithTag(false, LogLevel::Trace, Tag, __VA_ARGS__)
#define CLIENT_LOG_INFO_TAG(Tag, ...)     Snowflake::Logger::PrintMessageWithTag(false, LogLevel::Info, Tag, __VA_ARGS__)
#define CLIENT_LOG_DEBUG_TAG(Tag, ...)    Snowflake::Logger::PrintMessageWithTag(false, LogLevel::Debug, Tag, __VA_ARGS__)
#define CLIENT_LOG_WARN_TAG(Tag, ...)     Snowflake::Logger::PrintMessageWithTag(false, LogLevel::Warn, Tag, __VA_ARGS__)
#define CLIENT_LOG_ERROR_TAG(Tag, ...)    Snowflake::Logger::PrintMessageWithTag(false, LogLevel::Error, Tag, __VA_ARGS__)
#define CLIENT_LOG_CRITICAL_TAG(Tag, ...) Snowflake::Logger::PrintMessageWithTag(false, LogLevel::Critical, Tag, __VA_ARGS__)
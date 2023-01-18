#pragma once

#include "Core/Core.h"

#include <string>

namespace Snowflake
{
    struct ApplicationCommandLineArguments
    {
        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int Index)
        {
            return Args[Index];
        }
    };

    struct ApplicationSpecification
    {
        std::string Name;
        ApplicationCommandLineArguments CommandLineArguments;
    };
    
    class SNOWFLAKE_API Application
    {
    public:
        Application(const ApplicationSpecification& AppSpecification);
        virtual ~Application();

        virtual void OnInitialize() {}
        virtual void OnShutdown() {}

        void Start();
        void Close();

        static Application& GetInstance() { return *s_Instance; }

        bool IsRunning() { return bIsRunning; }
    private:
        static Application* s_Instance;

        ApplicationSpecification m_Specification;
        
        bool bIsRunning = true;
    };

    // Defined by the client application
    Application* CreateApplication(ApplicationCommandLineArguments CommandLineArguments);
}

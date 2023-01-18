#include <iostream>

#include "Application/ApplicationEntryPoint.h"

namespace Snowflake
{
    class SnowflakeEditorApp : public Application
    {
    public:
        SnowflakeEditorApp(const ApplicationSpecification& AppSpecification)
            : Application(AppSpecification) {}

        void OnInitialize() override {}
    };

    Application* CreateApplication(ApplicationCommandLineArguments CommandLineArguments)
    {
        ApplicationSpecification SnowflakeEditorAppSpecification;
        SnowflakeEditorAppSpecification.Name = "Snowflake Editor";
        SnowflakeEditorAppSpecification.CommandLineArguments = CommandLineArguments;
        
        return new SnowflakeEditorApp(SnowflakeEditorAppSpecification);
    }
}
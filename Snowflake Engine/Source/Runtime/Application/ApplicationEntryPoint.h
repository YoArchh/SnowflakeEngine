#pragma once

#include "Application/Application.h"

extern Snowflake::Application* Snowflake::CreateApplication(ApplicationCommandLineArguments CommandLineArguments);

bool bIsApplicationRunning = true;

namespace Snowflake
{
    int Main(int ArgsCount, char** Args)
    {
        while (bIsApplicationRunning)
        {
            Application* App = CreateApplication({ ArgsCount, Args });
            App->Start();
            delete App;
        }
        
        return 0;
    }
}

int main(int argc, char** argv)
{
    return Snowflake::Main(argc, argv);
}
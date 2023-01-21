#pragma once

#include "Core/Core.h"
#include "Core/CoreTypes.h"

#include "Events/Event.h"

#include <string>
#include <mutex>
#include <queue>

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
        virtual void OnShutdown();

        void Start();
        void Restart();
        void Close();

        virtual void OnEvent(Event& InEvent);

        template<typename EventFunction>
        void QueueEvent(EventFunction&& EventFunc)
        {
            m_EventQueue.push(EventFunc);
        }

        template<typename TEvent, bool bDispatchImmediately = false, typename ... EventArgs>
        void DispatchEvent(EventArgs&& ... EventArguments)
        {
            static_assert(std::is_assignable_v<Event, TEvent>);

            Ref<TEvent> TemplateEvent = CreateRef<TEvent>(std::forward<EventArgs>(EventArguments)...);
            if constexpr (bDispatchImmediately)
            {
                OnEvent(*TemplateEvent);
            }
            else
            {
                std::scoped_lock Lock(m_EventQueueMutex);
                m_EventQueue.push([TemplateEvent] { Application::GetInstance().OnEvent(*TemplateEvent); });
            }
        }

        static Application& GetInstance() { return *s_Instance; }

        bool IsRunning() { return bIsRunning; }

    private:
        void ProcessEvents();
        
    private:
        static Application* s_Instance;

        std::mutex m_EventQueueMutex;
        std::queue<std::function<void()>> m_EventQueue;
        std::vector<std::function<void(Event&)>> m_EventCallbacks;

        ApplicationSpecification m_Specification;
        
        bool bIsRunning = true;
    };

    // Defined by the client application
    Application* CreateApplication(ApplicationCommandLineArguments CommandLineArguments);
}

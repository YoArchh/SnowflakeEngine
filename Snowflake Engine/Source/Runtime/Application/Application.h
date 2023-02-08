#pragma once

#include "Core/CoreTypes.h"

#include "Events/ApplicationEvent.h"

#include "Window.h"

#include "Layers/LayerStack.h"

#include "ImGui/ImGuiLayer.h"

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
    
    class Application
    {
        using EventCallbackFunction = std::function<void(Event&)>;
        
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

        void PushLayer(Layer* InLayer);
        void PushOverlay(Layer* Overlay);

        void PopLayer(Layer* InLayer);
        void PopOverlay(Layer* Overlay);

        static Application& GetInstance() { return *s_Instance; }

        Window& GetWindow() { return *m_ApplicationWindow; }

        bool IsRunning() { return bIsRunning; }

    private:
        void ProcessEvents();

        bool OnWindowClose(WindowCloseEvent& Event);
        bool OnWindowResize(WindowResizeEvent& Event);
        bool OnWindowMinimize(WindowMinimizeEvent& Event);
        
    private:
        static Application* s_Instance;

        Scope<Window> m_ApplicationWindow;

        ImGuiLayer* m_ImGuiLayer;

        std::mutex m_EventQueueMutex;
        std::queue<std::function<void()>> m_EventQueue;
        std::vector<EventCallbackFunction> m_EventCallbacks;
        
        ApplicationSpecification m_Specification;
        LayerStack m_LayerStack;
        
        bool bIsWindowMinimized = false;
        bool bIsRunning = true;
    };

    // Defined by the client application
    Application* CreateApplication(ApplicationCommandLineArguments CommandLineArguments);
}

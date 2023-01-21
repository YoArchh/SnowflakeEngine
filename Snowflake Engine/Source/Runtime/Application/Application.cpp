#include "SnowflakePCH.h"
#include "Application.h"

#include "Logging/Logger.h"

#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

extern bool bIsApplicationRunning;

namespace Snowflake
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& AppSpecification)
        : m_Specification(AppSpecification)
    {
        s_Instance = this;
        
        LoggingSystem::Initialize();

        m_ApplicationWindow = Window::CreateWindow();
        m_ApplicationWindow->Initialize();
        m_ApplicationWindow->SetEventCallbackFunction([this](Event& InEvent) { OnEvent(InEvent); });
        m_ApplicationWindow->CenterWindow();

        m_ImGuiLayer = ImGuiLayer::Create();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        m_ApplicationWindow->SetEventCallbackFunction([](Event&) {});

        for (Layer* InLayer : m_LayerStack)
        {
            InLayer->OnDetach();
            delete InLayer;
        }
        
        LoggingSystem::Shutdown();
    }

    void Application::Start()
    {
        OnInitialize();
        
        while (bIsRunning)
        {
            ProcessEvents();

            glClearColor(0.45f, 0.55f, 0.65f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (!bIsWindowMinimized)
            {
                /*----------------*/
                /* -- Updating -- */
                /*----------------*/
                
                for (Layer* InLayer : m_LayerStack)
                    InLayer->OnUpdate();

                DispatchEvent<ApplicationUpdateEvent, true>(m_Specification.Name);

                /*-----------------*/
                /* -- Rendering -- */
                /*-----------------*/

                m_ImGuiLayer->Begin();

                for (Layer* InLayer : m_LayerStack)
                    InLayer->OnUIRender();

                m_ImGuiLayer->End();

                DispatchEvent<ApplicationRenderEvent, true>(m_Specification.Name);
                
                m_ApplicationWindow->SwapBuffers();

                /*---------------*/
                /* -- Ticking -- */
                /*---------------*/

                for (Layer* InLayer : m_LayerStack)
                    InLayer->OnTick();
            
                DispatchEvent<ApplicationTickEvent, true>(m_Specification.Name);
            }
        }

        OnShutdown();
    }

    void Application::Restart()
    {
        bIsRunning = false;
    }

    void Application::Close()
    {
        bIsRunning = false;
        bIsApplicationRunning = false;
    }

    void Application::OnShutdown()
    {
        m_EventCallbacks.clear();
    }

    void Application::OnEvent(Event& InEvent)
    {
        EventDispatcher Dispatcher(InEvent);
        Dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& Event) { return OnWindowClose(Event); });
        Dispatcher.Dispatch<WindowMinimizeEvent>([this](WindowMinimizeEvent& Event) { return OnWindowMinimize(Event); });
        
        for (auto Iterator = m_LayerStack.end(); Iterator != m_LayerStack.begin(); )
        {
            (*--Iterator)->OnEvent(InEvent);
            if (InEvent.bHandled)
                break;
        }
        
        if (InEvent.bHandled)
            return;
        
        for (auto& EventCallback : m_EventCallbacks)
        {
            if (InEvent.bHandled)
                continue;
            
            EventCallback(InEvent);
        }
    }

    void Application::PushLayer(Layer* InLayer)
    {
        m_LayerStack.PushLayer(InLayer);
    }

    void Application::PushOverlay(Layer* Overlay)
    {
        m_LayerStack.PushOverlay(Overlay);
    }

    void Application::PopLayer(Layer* InLayer)
    {
        m_LayerStack.PopLayer(InLayer);
    }

    void Application::PopOverlay(Layer* Overlay)
    {
        m_LayerStack.PopOverlay(Overlay);
    }

    bool Application::OnWindowClose(WindowCloseEvent& Event)
    {
        Close();

        return true;
    }

    bool Application::OnWindowMinimize(WindowMinimizeEvent& Event)
    {
        bIsWindowMinimized = Event.IsWindowMinimized();

        return true;
    }

    void Application::ProcessEvents()
    {
        m_ApplicationWindow->ProcessEvents();
        
        // Template arguments are deduced automatically, no need to write them explicitly.
        std::scoped_lock Lock(m_EventQueueMutex);

        while (!m_EventQueue.empty())
        {
            auto& EventFunction = m_EventQueue.front();
            EventFunction();

            m_EventQueue.pop();
        }
    }
}

#include "SnowflakePCH.h"
#include "ImGuiLayerOpenGL.h"

#include "Application/Application.h"

#include <GLFW/glfw3.h>

#include <imgui.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Snowflake
{
    void ImGuiLayerOpenGL::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& IO = ImGui::GetIO(); (void) IO;
        IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        IO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        
        IO.FontDefault = IO.Fonts->AddFontFromFileTTF("Resources/Fonts/ConfigRoundedSemibold.ttf", 16.0f);

        ImGui::StyleColorsDark();

        ImGuiStyle& Style = ImGui::GetStyle();
        if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            Style.WindowRounding = 0.0f;
            Style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        SetDarkThemeColors();

        Application& App = Application::GetInstance();
        auto* Window = static_cast<GLFWwindow*>(App.GetWindow().GetHandle());

        ImGui_ImplGlfw_InitForOpenGL(Window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayerOpenGL::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayerOpenGL::OnUIRender()
    {
        static bool bShowDemoWindow = true;
        ImGui::ShowDemoWindow(&bShowDemoWindow);
    }

    void ImGuiLayerOpenGL::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayerOpenGL::End()
    {
        Application& App = Application::GetInstance();
        int WindowWidth = App.GetWindow().GetWidth();
        int WindowHeight = App.GetWindow().GetHeight();
        
        ImGuiIO& IO = ImGui::GetIO();
        IO.DisplaySize = { static_cast<float>(WindowWidth), static_cast<float>(WindowHeight) };

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* CurrentContextBackup = glfwGetCurrentContext();

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();

            glfwMakeContextCurrent(CurrentContextBackup);
        }
    }
}

#pragma once

namespace Snowflake
{
    enum class RendererAPIType
    {
        OpenGL, Vulkan, Direct3D11, Direct3D12
    };

    class RendererAPI
    {
    public:
        static RendererAPIType GetCurrentAPI() { return s_CurrentRendererAPI; }
        static void SetCurrentAPI(RendererAPIType RendererAPI) { s_CurrentRendererAPI = RendererAPI; }
        
    private:
        inline static RendererAPIType s_CurrentRendererAPI = RendererAPIType::OpenGL;
    };
}
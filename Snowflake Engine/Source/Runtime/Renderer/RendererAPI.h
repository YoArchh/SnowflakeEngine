#pragma once

namespace Snowflake
{
    enum class BufferMask
    {
        Color = 1,
        Depth = 2,
        Stencil = 3,
        
        ColorAndDepth = 4
    };

    enum class PrimitiveType
    {
        Triangles = 1,
        Lines = 2
    };
    
    enum class RendererAPIType
    {
        OpenGL = 1,
        Vulkan = 2,
        Direct3D11 = 3,
        Direct3D12 = 4
    };

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;
        
        virtual void Initialize() = 0;
        
        virtual void Clear(BufferMask InBufferMask) = 0;
        
        virtual void ClearColor(float Red, float Green, float Blue, float Alpha) = 0;

        virtual void DrawIndexed(uint32_t Count, PrimitiveType DrawType, bool bDepthTest = true) = 0;
        
        static RendererAPIType GetCurrentAPI() { return s_CurrentRendererAPI; }
        static void SetCurrentAPI(RendererAPIType RendererAPI) { s_CurrentRendererAPI = RendererAPI; }

        static Scope<RendererAPI> Create();
        
    private:
        inline static RendererAPIType s_CurrentRendererAPI = RendererAPIType::OpenGL;
    };
}
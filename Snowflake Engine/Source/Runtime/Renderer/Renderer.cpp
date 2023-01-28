#include "SnowflakePCH.h"
#include "Renderer.h"

namespace Snowflake
{
    Scope<RendererAPI> Renderer::s_RendererAPI = nullptr;
    
    void Renderer::Initialize()
    {
        s_RendererAPI = RendererAPI::Create();
        
        s_RendererAPI->Initialize();
    }

    void Renderer::Clear(BufferMask InBufferMask)
    {
        s_RendererAPI->Clear(InBufferMask);
    }
    
    void Renderer::ClearColor(float Red, float Green, float Blue, float Alpha)
    {
        s_RendererAPI->ClearColor(Red, Green, Blue, Alpha);
    }

    void Renderer::DrawIndexed(uint32_t Count, PrimitiveType DrawType, bool bDepthTest)
    {
        s_RendererAPI->DrawIndexed(Count, DrawType, bDepthTest);
    }
}

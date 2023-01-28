#pragma once

#include "RendererAPI.h"

namespace Snowflake
{
    class Renderer
    {
    public:
        static void Initialize();

        static void Clear(BufferMask InBufferMask);
        
        static void ClearColor(float Red, float Green, float Blue, float Alpha);
        
        static RendererAPIType GetCurrentAPI() { return RendererAPI::GetCurrentAPI(); }
        static void SetCurrentAPI(RendererAPIType RendererAPI) { return RendererAPI::SetCurrentAPI(RendererAPI); }

        static void DrawIndexed(uint32_t Count, PrimitiveType DrawType, bool bDepthTest = true);
    private:
        static Scope<RendererAPI> s_RendererAPI;
    };
}

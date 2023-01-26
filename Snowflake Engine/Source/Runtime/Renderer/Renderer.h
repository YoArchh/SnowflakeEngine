#pragma once

#include "RendererAPI.h"

namespace Snowflake
{
    class Renderer
    {
    public:
        static RendererAPIType GetCurrentAPI() { return RendererAPI::GetCurrentAPI(); }
        static void SetCurrentAPI(RendererAPIType RendererAPI) { return RendererAPI::SetCurrentAPI(RendererAPI); }
    };
}

#include "SnowflakePCH.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "OpenGLRHI/OpenGLVertexArray.h"

namespace Snowflake
{
    Ref<VertexArray> VertexArray::CreateVertexArray()
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPIType::OpenGL: return CreateRef<OpenGLVertexArray>();
            case RendererAPIType::Vulkan: ENGINE_VERIFY(false, "Failed to create vertex array! Vulkan isn't supported!") return nullptr;
            case RendererAPIType::Direct3D11: ENGINE_VERIFY(false, "Failed to create vertex array! Direct3D11 isn't supported!") return nullptr;
            case RendererAPIType::Direct3D12: ENGINE_VERIFY(false, "Failed to create vertex array! Direct3D12 isn't supported!") return nullptr;
            default: ENGINE_VERIFY(false, "Failed to create vertex array! Unknown/unsupported graphics API!") return nullptr;
        }
    }
}

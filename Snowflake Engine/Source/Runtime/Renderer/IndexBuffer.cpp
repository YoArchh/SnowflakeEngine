#include "SnowflakePCH.h"
#include "IndexBuffer.h"

#include "Renderer/Renderer.h"

#include "OpenGLRHI/OpenGLIndexBuffer.h"

namespace Snowflake
{
    Ref<IndexBuffer> IndexBuffer::CreateIndexBuffer(void* BufferData, uint32_t BufferSize)
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPIType::OpenGL: return CreateRef<OpenGLIndexBuffer>(BufferData, BufferSize);
            case RendererAPIType::Vulkan: ENGINE_VERIFY(false, "Failed to create index buffer! Vulkan isn't supported!") return nullptr;
            case RendererAPIType::Direct3D11: ENGINE_VERIFY(false, "Failed to create index buffer! Direct3D11 isn't supported!") return nullptr;
            case RendererAPIType::Direct3D12: ENGINE_VERIFY(false, "Failed to create index buffer! Direct3D12 isn't supported!") return nullptr;
            default: ENGINE_VERIFY(false, "Failed to create vertex buffer! Unknown/unsupported graphics API!") return nullptr;
        }
    }
}

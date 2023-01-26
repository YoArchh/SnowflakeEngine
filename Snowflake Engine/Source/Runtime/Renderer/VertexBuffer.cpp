#include "SnowflakePCH.h"
#include "VertexBuffer.h"

#include "Renderer/Renderer.h"

#include "OpenGLRHI/OpenGLVertexBuffer.h"

namespace Snowflake
{
    Ref<VertexBuffer> VertexBuffer::CreateVertexBuffer(void* BufferData, uint32_t BufferSize, VertexBufferUsage BufferUsage /* = VertexBufferUsage::Static */)
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPIType::OpenGL: return CreateRef<OpenGLVertexBuffer>(BufferData, BufferSize, BufferUsage);
            case RendererAPIType::Vulkan: ENGINE_VERIFY(false, "Failed to create vertex buffer! Vulkan isn't supported!") return nullptr;
            case RendererAPIType::Direct3D11: ENGINE_VERIFY(false, "Failed to create vertex buffer! Direct3D11 isn't supported!") return nullptr;
            case RendererAPIType::Direct3D12: ENGINE_VERIFY(false, "Failed to create vertex buffer! Direct3D12 isn't supported!") return nullptr;
            default: ENGINE_VERIFY(false, "Failed to create vertex buffer! Unknown/unsupported graphics API!") return nullptr;
        }
    }
}

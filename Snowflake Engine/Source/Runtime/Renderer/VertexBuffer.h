#pragma once

namespace Snowflake
{
    enum VertexBufferUsage
    {
        Static = 35044,
        Dynamic = 35048
    };
    
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Ref<VertexBuffer> CreateVertexBuffer(void* BufferData, uint32_t BufferSize, VertexBufferUsage BufferUsage = VertexBufferUsage::Static);
    };
}

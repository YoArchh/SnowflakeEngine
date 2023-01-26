#pragma once

namespace Snowflake
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static Ref<IndexBuffer> CreateIndexBuffer(void* BufferData, uint32_t BufferSize);
    };
}

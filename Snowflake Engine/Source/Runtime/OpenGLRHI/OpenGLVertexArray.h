#pragma once

#include "Renderer/VertexArray.h"

namespace Snowflake
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& InVertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& InIndexBuffer) override;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
        virtual const Ref<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }

    private:
        uint32_t m_VertexArrayHandle;

        uint32_t m_VertexBufferIndex = 0;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}

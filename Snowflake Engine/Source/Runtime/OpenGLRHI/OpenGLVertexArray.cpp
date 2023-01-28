#include "SnowflakePCH.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Snowflake
{
    namespace Utils
    {
        static GLenum ConvertShaderDataTypeToOpenGLBaseType(ShaderDataType InShaderDataType)
        {
            switch (InShaderDataType)
            {
                case ShaderDataType::None:    return 0;
                case ShaderDataType::Float:   return GL_FLOAT;
                case ShaderDataType::Float2:  return GL_FLOAT;
                case ShaderDataType::Float3:  return GL_FLOAT;
                case ShaderDataType::Float4:  return GL_FLOAT;
                case ShaderDataType::Matrix3: return GL_FLOAT;
                case ShaderDataType::Matrix4: return GL_FLOAT;
                case ShaderDataType::Int:     return GL_INT;
                case ShaderDataType::In2:     return GL_INT;
                case ShaderDataType::Int3:    return GL_INT;
                case ShaderDataType::Int4:    return GL_INT;
                case ShaderDataType::Boolean: return GL_BOOL;
                default: ENGINE_ASSERT(false, "Failed to get shader data type size! Unknown data type!") return 0;
            }
        }
    }
    
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_VertexArrayHandle);
        glBindVertexArray(m_VertexArrayHandle);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_VertexArrayHandle);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_VertexArrayHandle);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& InVertexBuffer)
    {
        ENGINE_ASSERT(InVertexBuffer->GetBufferLayout().GetElements().size(), "Failed to add vertex buffer! It has no buffer layout!")

        Bind();
        InVertexBuffer->Bind();

        const auto& Layout = InVertexBuffer->GetBufferLayout();
        for (const auto& BufferElement : Layout)
        {
            auto GLBaseType = Utils::ConvertShaderDataTypeToOpenGLBaseType(BufferElement.DataType);
            glEnableVertexAttribArray(m_VertexBufferIndex);
            
            if (GLBaseType == GL_INT)
            {
                glVertexAttribIPointer(m_VertexBufferIndex,
                    BufferElement.GetComponentCount(),
                    GLBaseType,
                    Layout.GetStride(),
                    reinterpret_cast<const void*>(static_cast<intptr_t>(BufferElement.Offset)));
            }
            else
            {
                glVertexAttribPointer(m_VertexBufferIndex,
                    BufferElement.GetComponentCount(),
                    GLBaseType,
                    BufferElement.bNormalized ? GL_TRUE : GL_FALSE,
                    Layout.GetStride(),
                    reinterpret_cast<const void*>(static_cast<intptr_t>(BufferElement.Offset)));
            }

            m_VertexBufferIndex++;
        }
        
        m_VertexBuffers.push_back(InVertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& InIndexBuffer)
    {
        Bind();
        InIndexBuffer->Bind();

        m_IndexBuffer = InIndexBuffer;
    }
}

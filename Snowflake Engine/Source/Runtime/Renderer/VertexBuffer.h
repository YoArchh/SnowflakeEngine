#pragma once

namespace Snowflake
{
    enum class ShaderDataType
    {
        None = 0,

        Float, Float2, Float3, Float4,
        Matrix3, Matrix4,
        Int, In2, Int3, Int4,
        Boolean
    };

    static uint32_t GetShaderDataTypeSize(ShaderDataType InShaderDataType)
    {
        switch (InShaderDataType)
        {
            case ShaderDataType::None:    return 0;
            case ShaderDataType::Float:   return 4;
            case ShaderDataType::Float2:  return 4 * 2;
            case ShaderDataType::Float3:  return 4 * 3;
            case ShaderDataType::Float4:  return 4 * 4;
            case ShaderDataType::Matrix3: return 4  * 3 * 3;
            case ShaderDataType::Matrix4: return 4 * 4 * 4;
            case ShaderDataType::Int:     return 4;
            case ShaderDataType::In2:     return 4 * 2;
            case ShaderDataType::Int3:    return 4 * 3;
            case ShaderDataType::Int4:    return 4 * 4;
            case ShaderDataType::Boolean: return 1;
            default: ENGINE_ASSERT(false, "Failed to get shader data type size! Unknown data type!") return 0;
        }
    }

    struct BufferElement
    {
        std::string Name;
        ShaderDataType DataType;
        uint32_t Size;
        uint32_t Offset;
        bool bNormalized;

        BufferElement() = default;

        BufferElement(ShaderDataType InShaderDataType, const std::string& ElementName, bool bIsNormalized = false)
            : Name(ElementName), DataType(InShaderDataType), Size(GetShaderDataTypeSize(InShaderDataType)), Offset(0), bNormalized(bIsNormalized) {}

        uint32_t GetComponentCount() const
        {
            switch (DataType)
            {
                case ShaderDataType::None:    return 0;
                case ShaderDataType::Float:   return 1;
                case ShaderDataType::Float2:  return 2;
                case ShaderDataType::Float3:  return 3;
                case ShaderDataType::Float4:  return 4;
                case ShaderDataType::Matrix3: return 3 * 3;
                case ShaderDataType::Matrix4: return 4 * 4;
                case ShaderDataType::Int:     return 1;
                case ShaderDataType::In2:     return 2;
                case ShaderDataType::Int3:    return 3;
                case ShaderDataType::Int4:    return 4;
                case ShaderDataType::Boolean: return 1;
                default: ENGINE_ASSERT(false, "Failed to get component count! Unknown shader data type!") return 0;
            }
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement>& BufferElements)
            : m_BufferElements(BufferElements)
        {
            CalculateOffsetsAndStride();
        }

        inline uint32_t GetStride() const { return m_Stride; }
        inline const std::vector<BufferElement>& GetElements() const { return m_BufferElements; }

        std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); }
        
    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t Offset = 0;
            m_Stride = 0;

            for (auto& BufferElement : m_BufferElements)
            {
                BufferElement.Offset = Offset;
                Offset += BufferElement.Size;
                m_Stride += BufferElement.Size;
            }
        }

    private:
        std::vector<BufferElement> m_BufferElements;
        uint32_t m_Stride = 0;
    };
    
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

        virtual const BufferLayout& GetBufferLayout() const = 0;
        virtual void SetBufferLayout(const BufferLayout& InBufferLayout) = 0;

        static Ref<VertexBuffer> CreateVertexBuffer(void* BufferData, uint32_t BufferSize, VertexBufferUsage BufferUsage = VertexBufferUsage::Static);
    };
}

#pragma once
#include "Hazel/Core.h"
#include "ShaderDataType.h"

namespace Hazel
{
    struct BufferElement
    {
        ShaderDataType Type;
        std::string Name;
        uint Offset;
        uint Size;
        bool Normalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Type{ type }, Name{ name }, Size{ ShaderDataTypeSize(type) }, Offset{ 0 }, Normalized{ normalized }
        {
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout(const std::initializer_list<BufferElement>& elements);
        ~BufferLayout() {}

        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        inline const uint GetStride() const { return m_Stride; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
    private:
        std::vector<BufferElement> m_Elements;
        uint m_Stride;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static std::shared_ptr<VertexBuffer> Create(float* vertices, uint size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual uint GetCount() const = 0;

        static std::shared_ptr<IndexBuffer> Create(uint* indices, uint count);
    };
}
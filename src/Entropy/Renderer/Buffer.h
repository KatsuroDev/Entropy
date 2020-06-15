#pragma once

namespace Entropy {

    // Vertex buffer
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Attach() = 0;
        virtual void Detach() = 0;

        // Void ptr because it's an undefined array
        virtual void Fill(const void* data, unsigned int size) = 0;

        static VertexBuffer* Create(float* vertices, unsigned int size);
        static VertexBuffer* Create(unsigned int size);
    };



    // Index buffer
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Attach() = 0;
        virtual void Detach() = 0;

        virtual unsigned int GetCount() = 0;

        static IndexBuffer* Create(unsigned int* indices, unsigned int size);
    };
}

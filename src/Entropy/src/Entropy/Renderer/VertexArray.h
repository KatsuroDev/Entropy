#pragma once

#include "Buffer.h"

// Contains the vertex and index buffers
// Interface or abstract class
namespace Entropy {

    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        // Pure virtual methods
        virtual void Attach() const = 0;
        virtual void Detach() const = 0;

        virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
        virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;

        virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const = 0;
        virtual const IndexBuffer& GetIndexBuffer() const = 0;

        // API is the default Rendering API
        static VertexArray* Create();
    };
}

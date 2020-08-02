#pragma once

#include "Buffer.h"

// Contains the vertex and index buffers
// Interface or abstract class
namespace Entropy {

    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        // Pure virtual methods
        virtual void Attach() const = 0;
        virtual void Detach() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

        // API is the default Rendering API
        static Ref<VertexArray> Create();
    };
}

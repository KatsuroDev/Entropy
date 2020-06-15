#pragma once

#include "VertexArray.h"

namespace Entropy {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        virtual ~OpenGLVertexArray();

        virtual void Attach() override;
        virtual void Detach() override;

        virtual void AddVertexBuffer(const VertexBuffer& vertexBuffer) override;
        virtual void SetIndexBuffer(const IndexBuffer& indexBuffer) override;

        // Getters
        virtual const std::vector<VertexBuffer>& GetVertexBuffers() { return m_VertexBuffers; }
        virtual const IndexBuffer& GetIndexBuffer() { return *m_IndexBuffer; }

    private:
        std::vector<VertexBuffer> m_VertexBuffers;
        IndexBuffer* m_IndexBuffer;
        unsigned int m_RendererID;
        unsigned int m_VertexBufferIndex = 0;
    };
}

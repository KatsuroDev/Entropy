#pragma once

#include "../../Entropy/Renderer/VertexArray.h"

namespace Entropy {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        virtual ~OpenGLVertexArray();

        virtual void Attach() const override;
        virtual void Detach() const override;

        virtual void AddVertexBuffer(const VertexBuffer& vertexBuffer) override;
        virtual void SetIndexBuffer(const IndexBuffer& indexBuffer) override;

        // Getters
        virtual const std::vector<VertexBuffer>& GetVertexBuffers() const { return m_VertexBuffers; }
        virtual const IndexBuffer& GetIndexBuffer() const { return *m_IndexBuffer; }

    private:
        std::vector<VertexBuffer> m_VertexBuffers;
        IndexBuffer* m_IndexBuffer;
        unsigned int m_RendererID;
        unsigned int m_VertexBufferIndex = 0;
    };
}

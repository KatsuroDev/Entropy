#pragma once

#include "../../Entropy/Renderer/VertexArray.h"

namespace Entropy {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Attach() const override;
        virtual void Detach() const override;

        virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
        virtual void SetIndexBuffer(IndexBuffer* indexBuffer) override;

        // Getters
        virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const { return m_VertexBuffers; }
        virtual const IndexBuffer& GetIndexBuffer() const { return *m_IndexBuffer; }

    private:
        unsigned int m_RendererID;
        unsigned int m_VertexBufferIndex = 0;
        std::vector<VertexBuffer*> m_VertexBuffers;
        IndexBuffer* m_IndexBuffer = nullptr;
    };
}

#pragma once

#include "Buffer.h"

namespace Entropy {

    // Vertex buffer
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(unsigned int size);
        OpenGLVertexBuffer(float* vertices, unsigned int size);
        virtual ~OpenGLVertexBuffer();

        virtual void Attach() override;
        virtual void Detach() override;

        virtual void Fill(const void* data, unsigned int size) override;

    private:
        unsigned int m_RendererID;
    };




    // Index buffer
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
        virtual ~OpenGLIndexBuffer();

        virtual void Attach() override;
        virtual void Detach() override;

        virtual unsigned int GetCount() { return m_Count; };

    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    };
}

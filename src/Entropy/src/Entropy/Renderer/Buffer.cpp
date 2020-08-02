#include "Buffer.h"

#include "../../Platform/OpenGL/OpenGLBuffer.h"

#include "Renderer.h"

namespace Entropy {

    // Vertex buffer
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(vertices, size);
        case RenderingAPI::API::None:
            NT_FATAL("Rendering API not supported");
            return nullptr;
        }

        NT_FATAL("Unknown Rendering API");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(size);
        case RenderingAPI::API::None:
            NT_FATAL("Rendering API not supported");
            return nullptr;
        }

        NT_FATAL("Unknown Rendering API");
        return nullptr;
    }



    // Index buffer
    Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(indices, size);
        case RenderingAPI::API::None:
            NT_FATAL("Rendering API not supported");
            return nullptr;
        }

        NT_FATAL("Unknown Rendering API");
        return nullptr;
    }
}

#include "Buffer.h"

#include "../../Platform/OpenGL/OpenGLBuffer.h"

#include "Renderer.h"
#include "../Core/Logger.h"

namespace Entropy {

    // Vertex buffer
    VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            NT_INFO("Created a new OpenGL vertex buffer");
            return new OpenGLVertexBuffer(vertices, size);
        case RenderingAPI::API::None:
            NT_FATAL("Rendering API not supported");
            return nullptr;
        }

        return nullptr;
    }

    VertexBuffer* VertexBuffer::Create(unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            NT_INFO("Created a new OpenGL vertex buffer");
            return new OpenGLVertexBuffer(size);
        case RenderingAPI::API::None:
            NT_FATAL("Rendering API not supported");
            return nullptr;
        }

        return nullptr;
    }



    // Index buffer
    IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            NT_INFO("Created a new OpenGL index buffer");
            return new OpenGLIndexBuffer(indices, size);
        case RenderingAPI::API::None:
            NT_FATAL("Rendering API not supported");
            return nullptr;
        }

        return nullptr;
    }
}

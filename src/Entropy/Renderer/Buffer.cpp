#include "Buffer.h"

#include "OpenGLBuffer.h"

#include "Renderer.h"
#include "Logger.h"

namespace Entropy {

    // Vertex buffer
    VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        break;
        case RenderingAPI::API::None:
            Logger::FATAL("Rendering API not supported");
        }
    }

    VertexBuffer* VertexBuffer::Create(unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            return new OpenGLVertexBuffer(size);
        break;
        case RenderingAPI::API::None:
            Logger::FATAL("Rendering API not supported");
        }
    }



    // Index buffer
    IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indices, size);
        break;
        case RenderingAPI::API::None:
            Logger::FATAL("Rendering API not supported");
        }
    }
}

#include "VertexArray.h"

// include all supported vertex arrays here
#include "../../Platform/OpenGL/OpenGLVertexArray.h"

#include "Renderer.h"
#include "../Core/Logger.h"

namespace Entropy {

    VertexArray* VertexArray::Create()
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            return new OpenGLVertexArray();
        case RenderingAPI::API::None:
            NT_FATAL("Rendering API not supported");
            return nullptr;
        }

        return nullptr;
    }
}

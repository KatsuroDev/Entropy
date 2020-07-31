#include "VertexArray.h"

#include "../Core/Core.h"

#include "Renderer.h"

// include all supported vertex arrays here
#include "../../Platform/OpenGL/OpenGLVertexArray.h"

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

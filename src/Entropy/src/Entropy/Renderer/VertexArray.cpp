#include "VertexArray.h"

#include "Renderer.h"

// include all supported vertex arrays here
#include "../../Platform/OpenGL/OpenGLVertexArray.h"

namespace Entropy {

    Ref<VertexArray> VertexArray::Create()
    {
        switch(Renderer::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            return CreateRef<OpenGLVertexArray>();
        case RenderingAPI::API::None:
            NT_FATAL("Rendering API not supported");
            return nullptr;
        }

        NT_FATAL("Unknown Rendering API");
        return nullptr;
    }
}

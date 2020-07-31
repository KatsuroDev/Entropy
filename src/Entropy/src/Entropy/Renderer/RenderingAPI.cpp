#include "RenderingAPI.h"

#include "../Core/Core.h"
// include all supported APIs here
#include "../../Platform/OpenGL/OpenGLRenderingAPI.h"

namespace Entropy {

    // Default Graphics API is openGL
    // That needs to be setted al the very beginning of the program
    RenderingAPI::API RenderingAPI::s_API = RenderingAPI::API::OpenGL;

    RenderingAPI* RenderingAPI::Create()
    {
        switch(RenderingAPI::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            NT_TRACE("Created the OpenGL rendering API");
            return new OpenGLRenderingAPI();
        case RenderingAPI::API::None:
            NT_FATAL(0, "Rendering API not supported");
            return nullptr;
        }

        return nullptr;
    }
}

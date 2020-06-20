#include "RenderingAPI.h"

// include all supported APIs here
#include "../../Platform/OpenGL/OpenGLRenderingAPI.h"

#include "../Core/Logger.h"

namespace Entropy {

    // Default Graphics API is openGL
    // That needs to be setted al the very beginning of the program
    RenderingAPI::API RenderingAPI::s_API = RenderingAPI::API::OpenGL;

    RenderingAPI* RenderingAPI::Create()
    {
        switch(RenderingAPI::GetAPI())
        {
        case RenderingAPI::API::OpenGL:
            return new OpenGLRenderingAPI();
            Logger::Info("Created the OpenGL rendering API");
        break;
        case RenderingAPI::API::None:
            Logger::FATAL("Rendering API not supported");
        }
    }
}

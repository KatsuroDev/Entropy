#include "RenderingAPI.h"

// include all supported APIs here
#include "OpenGLRenderingAPI.h"

#include "Logger.h"

namespace Entropy {

    RenderingAPI::API RenderingAPI::s_API = RenderingAPI::API::None;

    RenderingAPI* RenderingAPI::Get(RenderingAPI::API API)
    {
        // Setting the API type
        RenderingAPI::s_API = API;

        switch(API)
        {
        case RenderingAPI::API::OpenGL:
            return new OpenGLRenderingAPI();
        break;
        case RenderingAPI::API::None:
            Logger::FATAL("Rendering API not supported");
        }
    }
}

#include "RenderingAPI.h"

// include all supported APIs here
#include "OpenGLRenderingAPI.h"

#include "Logger.h"

namespace Entropy {

    RenderingAPI* RenderingAPI::Get(RenderingAPI::API API)
    {
        Logger::Info("Setting up the right rendering API...");

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

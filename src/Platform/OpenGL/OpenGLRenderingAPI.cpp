#include "OpenGLRenderingAPI.h"

#include "Logger.h"

#define GLEW_STATIC
#include <GL/glew.h>

// Provides all declarations for OpenGL rendering API calls

namespace Entropy {

    void OpenGLRenderingAPI::Init()
    {
        // Init glew
        if(glewInit() != GLEW_OK)
            Logger::FATAL("Renderer could not init GLEW!");
        Logger::Info("Initialized OpenGL");
    }

    void OpenGLRenderingAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderingAPI::SetClearColor(const Vector4f& rgba)
    {
        glClearColor(rgba.X, rgba.Y, rgba.Z, rgba.W);
    }

    void OpenGLRenderingAPI::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        glViewport(x, y, width, height);
    }
}

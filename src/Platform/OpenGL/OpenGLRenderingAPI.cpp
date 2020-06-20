#include "OpenGLRenderingAPI.h"

#include <GL/glew.h>

namespace Entropy {


    void OpenGLRenderingAPI::Init()
    {
        // Enabling alpha channel and blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
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

    void OpenGLRenderingAPI::Draw(const VertexArray& vertexArray, unsigned int indexCount)
    {
        unsigned int count = indexCount ? indexCount : vertexArray.GetIndexBuffer().GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

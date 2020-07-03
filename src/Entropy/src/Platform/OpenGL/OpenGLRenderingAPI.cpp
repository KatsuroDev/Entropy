#include "OpenGLRenderingAPI.h"

#include <GL/glew.h>

namespace Entropy {


    void OpenGLRenderingAPI::Init()
    {
        // Gamma correction
        glEnable(GL_FRAMEBUFFER_SRGB);
        // Enabling alpha channel and blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderingAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderingAPI::SetClearColor(const glm::vec4& rgba)
    {
        glClearColor(rgba.x, rgba.y, rgba.z, rgba.w);
    }

    void OpenGLRenderingAPI::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRenderingAPI::Draw(VertexArray* vertexArray, unsigned int indexCount)
    {
        unsigned int count = indexCount ? indexCount : vertexArray->GetIndexBuffer().GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLRenderingAPI::DrawInstanced(VertexArray* vertexArray, unsigned int repeatCount, unsigned int indexCount)
    {
        unsigned int count = indexCount ? indexCount : vertexArray->GetIndexBuffer().GetCount();
        glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr, repeatCount);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
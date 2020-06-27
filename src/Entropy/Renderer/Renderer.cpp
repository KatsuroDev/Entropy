#include "Renderer.h"

#include "../Core/Logger.h"

namespace Entropy {

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::Dispose()
    {
        NT_INFO("Disposed of renderer ressources");
    }

    void Renderer::AttachData(/* shader */ const VertexArray& vertexArray, const Matrix4f& transform)
    {
        // TODO: Attach shaders
        // set uniform the transformation matrix to the shader
        // set uniform the projection matrix to the shader

        vertexArray.Attach();
        RenderCommand::DrawPending(vertexArray);
        NT_TRACE("RENDERER: Attached data");
    }

    void Renderer::OnWindowResize(unsigned int width, unsigned int height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
        NT_TRACE("RENDERER: Reset viewport");
    }
}

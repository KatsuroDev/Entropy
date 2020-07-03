#pragma once

#include "../../Entropy/Renderer/RenderingAPI.h"

namespace Entropy {

    class OpenGLRenderingAPI : public RenderingAPI
    {
    public:
        virtual void Init() override;
        virtual void SetClearColor(const glm::vec4& rgba) override;
        virtual void Clear() override;
        virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
        virtual void Draw(VertexArray* vertexArray, unsigned int indexCount = 0) override;
        virtual void DrawInstanced(VertexArray* vertexArray, unsigned int repeatCount, unsigned int indexCount = 0);
    };
}

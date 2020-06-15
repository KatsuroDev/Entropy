#pragma once

#include "RenderingAPI.h"

namespace Entropy {

    class OpenGLRenderingAPI : public RenderingAPI
    {
    public:
        virtual void Init() override;
        virtual void SetClearColor(const Vector4f& rgba) override;
        virtual void Clear() override;
        virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
        virtual void Draw(const VertexArray& vertexArray, unsigned int indexCount = 0) override;
    };
}

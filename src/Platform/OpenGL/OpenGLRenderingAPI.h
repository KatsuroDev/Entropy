#pragma once

#include "RenderingAPI.h"

namespace Entropy {

    class OpenGLRenderingAPI : public RenderingAPI
    {
    public:
        virtual void Init() override;
        virtual void SetClearColor(const Vector4f& rgba) override;
        virtual void Clear() override;
        virtual void SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
    };
}

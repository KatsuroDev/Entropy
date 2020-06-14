#pragma once

#include "Vector4f.h"

// Provides generic methods communicating with all supported rendering APIs
// Implementations are done in the corresponding
// Platform/<platform name>/<platform name>RenderingAPI classes
// This is done so the renderer doesn't have to care which API is being use internally
namespace Entropy {

    class RenderingAPI
    {
    public:
        // All pur virtual
        virtual void Init() = 0;
        virtual void Clear(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const Vector4f& RGBA);

    private:
        RenderingAPI m_RenderingAPI;
    };
}

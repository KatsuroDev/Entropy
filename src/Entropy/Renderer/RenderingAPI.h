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
        // Supported APIs
        enum class API
		{
            // None will cause an assertion
            None = 0, OpenGL = 1
		};

        // All pure virtual
        virtual void Init() = 0;
        virtual void SetClearColor(const Vector4f& rgba) = 0;
        virtual void Clear() = 0;
        virtual void SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;

        static API GetAPI() { return s_API; }

    private:
        static API s_API;
    };

    RenderingAPI* CreateRenderingAPI(RenderingAPI::API API);
}

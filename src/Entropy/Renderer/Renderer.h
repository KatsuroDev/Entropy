#pragma once

#include "RenderingAPI.h"
#include "VertexArrayObject.h"

namespace Entropy {

    class Renderer
    {
    public:
        // Sets rendering context coordinates
        // Manages VAO and IBO
        static void Init();
        static void Dispose();

        static unsigned int m_VAO;
        static unsigned int m_VBO;

        static RenderingAPI::API GetAPI() { return s_RenderingAPI->GetAPI(); }

    private:
        static RenderingAPI* s_RenderingAPI;
    };
}

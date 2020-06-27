#pragma once

#include "RenderingAPI.h"
#include "RenderCommand.h"

#include "../Core/Math/Matrix4f.h"
//TODO: instead of matrix, include camera wich incldes matrix

namespace Entropy {

    class Renderer
    {
    public:
        static void Init();
        static void Dispose();

        static void OnWindowResize(unsigned int width, unsigned int height);

        static void AttachData(/* shader */ const VertexArray& vertexArray, const Matrix4f& transform);

        static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
    };
}

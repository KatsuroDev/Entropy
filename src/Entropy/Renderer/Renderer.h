#pragma once

#include "RenderingAPI.h"
#include "VertexArray.h"

#include "Matrix4f.h"
//TODO: instead of matrix, include camera wich incldes matrix

namespace Entropy {

    class Renderer
    {
    public:
        static void Init();
        static void Dispose();
        // All Renderer commands
        static void SetClearColor(const Vector4f& rgba);
        static void Clear();
        static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        // TODO: Draw vertex array

        static void SetData(/* shader */ const VertexArray& vertexArray, const Matrix4f& transform);

        static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }

    private:
        static RenderingAPI* s_RenderingAPI;
    };
}

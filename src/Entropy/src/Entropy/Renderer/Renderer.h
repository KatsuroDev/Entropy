#pragma once

#include "RenderingAPI.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"
#include "CameraController.h"

namespace Entropy {

    class Renderer
    {
    public:
        static void Init();
        static void Dispose();

        static void OnWindowResize(unsigned int width, unsigned int height);

        static void Draw(Shader* shader, VertexArray* vertexArray, const glm::mat4& transform, const Camera& camera);
        static void DrawInstanced(Shader* shader, VertexArray* vertexArray, const glm::mat4& transform, const Camera& camera, unsigned int repeatCount);

        static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
    };
}

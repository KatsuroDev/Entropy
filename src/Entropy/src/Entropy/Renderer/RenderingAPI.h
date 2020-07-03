#pragma once

#include "VertexArray.h"

#include <GL/glm/vec4.hpp>

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

        virtual ~RenderingAPI() {}

        // All pure virtual
        virtual void Init() = 0;
        virtual void SetClearColor(const glm::vec4& rgba) = 0;
        virtual void Clear() = 0;
        virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
        virtual void Draw(VertexArray* vertexArray, unsigned int indexCount = 0) = 0;
        virtual void DrawInstanced(VertexArray* vertexArray, unsigned int repeatCount, unsigned int indexCount = 0) = 0;

        static API GetAPI() { return s_API; }

        static RenderingAPI* Create();

    private:
        static API s_API;
    };
}
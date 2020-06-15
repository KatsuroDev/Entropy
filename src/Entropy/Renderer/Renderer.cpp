#include "Renderer.h"

#include "Logger.h"

namespace Entropy {

    RenderingAPI* Renderer::s_RenderingAPI = nullptr;

    void Renderer::Init()
    {
        // ---------------------------------------------------------
        // Rendering API selection is done here
        // ---------------------------------------------------------
        s_RenderingAPI = RenderingAPI::Get(RenderingAPI::API::OpenGL);
        // Calling these before Getting the Graphics API would result in a
        // segmentation fault!
        // We do NOT need to test if RenderingAPI::Get() returns nullptr.
        // It's done internally and asserts the program if necessary
        s_RenderingAPI->Init();
        s_RenderingAPI->SetClearColor(Vector4f(0.0f, 0.39f, 0.65f, 1.0f));

        /*
        // Screen limits
        float screenTexCoord[] =
        {
            // Pos        // Tex Coord
            1.0f,  1.0f,  1.0f, 0.0f, // Top right
            1.0f, -1.0f,  1.0f, 1.0f, // Bottom right
           -1.0f, -1.0f,  0.0f, 1.0f, // Bottom left

           -1.0f, -1.0f,  0.0f, 1.0f, // Bottom left
           -1.0f,  1.0f,  0.0f, 0.0f, // Top left
            1.0f,  1.0f,  1.0f, 0.0f  // Top right
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(screenTexCoord), &screenTexCoord, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2* sizeof(float)));

        glBindVertexArray(0);
        */

        Logger::Info("Initialized renderer");
    }

    void Renderer::Dispose()
    {
        // Clearing ressources
        delete s_RenderingAPI;

        Logger::Info("Disposed of renderer ressources");
    }

    void Renderer::SetClearColor(const Vector4f& rgba)
    {
        s_RenderingAPI->SetClearColor(rgba);
    }

    void Renderer::Clear()
    {
        s_RenderingAPI->Clear();
    }

    void Renderer::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        s_RenderingAPI->SetViewport(x, y, width, height);
    }

    void Renderer::Draw(const VertexArray& vertexArray, unsigned int count)
    {
        s_RenderingAPI->Draw(vertexArray, count);
    }

    void Renderer::AttachData(/* shader */ const VertexArray& vertexArray, const Matrix4f& transform)
    {
        // TODO: Attach shaders
        // set uniform the transformation matrix to the shader
        // set uniform the projection matrix to the shader

        vertexArray.Attach();
        // Draw the vertex array
    }
}

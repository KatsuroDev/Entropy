#include "Renderer.h"

#include "Logger.h"

namespace Entropy {

    unsigned int Renderer::m_VAO = 0;
    unsigned int Renderer::m_VBO = 0;

    RenderingAPI* Renderer::s_RenderingAPI = nullptr;

    void Renderer::Init()
    {
        // Constructor called here
        s_RenderingAPI = CreateRenderingAPI(RenderingAPI::API::OpenGL);
        s_RenderingAPI->Init();
        s_RenderingAPI->SetClearColor(Vector4f(0.0f, 0.39f, 0.65f, 1.0f));

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

        /*
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
}

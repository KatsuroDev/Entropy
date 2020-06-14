#include "Renderer.h"

#include "Application.h"

namespace Entropy {

    unsigned int Renderer::m_VAO = 0;
    unsigned int Renderer::m_VBO = 0;

    void Renderer::Init()
    {
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
    }

    void Renderer::Dispose()
    {

    }
}
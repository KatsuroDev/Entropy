#pragma once

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

    private:

    };
}

#include "Application.h"

#include "Renderer.h"

namespace Entropy {

    Application::Application(int width, int height, const char* title)
    {
        // Create window for application here
        m_Window = new Window(width, height, title);

        // Init glew
        if(glewInit() != GLEW_OK)
            glfwTerminate();

        // Init the renderer
        Renderer::Init();
    }

    Application::~Application()
    {
        // Shutdown the renderer
        Renderer::Dispose();

        // Deleting window
        delete m_Window;
    }

    void Application::Run()
    {
        // Program loop here
        while(m_Running)
        {
            if (m_Window->ShouldClose())
                this->Terminate();

            // User games color
            glClearColor(0.0f, 0.39f, 0.65f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Render here


            // Swap front and back buffers
            m_Window->SwapBuffers();

            // Poll and process events
            m_Window->PollEvents();
        }
    }

    void Application::Terminate()
    {
        m_Running = false;
    }
}

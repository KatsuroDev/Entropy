#include "Application.h"

namespace Entropy {

    Application::Application(int width, int height, const char* title)
    {
        // Create window for application here
        m_Window = new Window(width, height, title);

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

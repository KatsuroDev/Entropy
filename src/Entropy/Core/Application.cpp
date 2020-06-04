#include "Application.h"

// TODO: include log
// TODO: include renderer

namespace Entro {

    // TODO: Implement an event system for the application

    // Application instance
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;

        // Create window for application here
        // TODO: Call CreateWindow in Window
        m_Window = new Window(800, 600, "Entropy Engine");
        
        // TODO: Init the renderer
    }

    Application::~Application()
    {
        // TODO: Shutdown the renderer
        
        // Deleting window
        delete m_Window;
    }

    void Application::Run()
    {
        // TODO: Program loop here
        while(!m_Window->ShouldClose())
        {
            // Render here
            // User games color
            glClearColor(0.0f, 0.39f, 0.65f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Swap front and back buffers
            m_Window->SwapBuffers();

            // Poll and process events
            m_Window->PollEvents();
        }
    }
}
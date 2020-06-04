#include "Application.h"
#include <iostream>

// TODO: Implement an event system for the application

// Application instance
Application* Application::s_Instance = nullptr;

Application::Application()
{
    s_Instance = this;

    // TODO: Create window for application here
    m_Window = new Window(800, 600, "Entropy Engine");
    // Init the renderer
}

Application::~Application()
{
    // Shutdown the renderer
}

void Application::Run()
{
    // TODO: Program loop here
    std::cout << "Hello, Entropy is started!\n";
    while(!m_Window->ShouldClose())
    {
        // Render here
        glClearColor(0.0f, 0.39f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int width, height;
        window.GetDimensions(width, height);
        std::cout << width << ", " << height << "\n";

        // Swap front and back buffers
        window.SwapBuffers();

        // Poll and process events
        window.PollEvents();
    }
}

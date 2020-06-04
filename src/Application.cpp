#include "Application.h"
#include <iostream>

// TODO: Implement an event system for the application

// Application instance
Application* Application::s_Instance = nullptr;

Application::Application()
{
    s_Instance = this;

    // Create window for application here
    // TODO: Call createWindow in Window
    m_Window = new Window(800, 600, "Entropy Engine");
    
    // TODO: Init the renderer
}

Application::~Application()
{
    // TODO: Shutdown the renderer
    
    // Clearing ressources
    delete m_Window;
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
        m_Window->GetDimensions(width, height);
        std::cout << width << ", " << height << "\n";

        // Swap front and back buffers
        m_Window->SwapBuffers();

        // Poll and process events
        m_Window->PollEvents();
    }
}

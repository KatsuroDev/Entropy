#include "Application.h"

#include "Renderer.h"

namespace Entropy {

    Application* Application::s_Instance = nullptr;

    Application::Application(int width, int height, const char* title)
    {
        Logger::Trace("Hello from the logger! Warming transistors...");

        s_Instance = this;

        // Create window for application here
        m_Window = new Window(width, height, title);

        // Init the renderer
        Renderer::Init();

        // Printing the selected Graphics API for debugging
        RenderingAPI::API api = Renderer::GetAPI();
        if (api == RenderingAPI::API::OpenGL)
            Logger::Info("Used Graphics API: OpenGL");
        else
            Logger::Info("None");
    }

    Application::~Application()
    {
        // Shutdown the renderer
        Renderer::Dispose();

        // Deleting window
        delete m_Window;


        Logger::Trace("Hey! Come back next time.");
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        //dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        //dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

        // Handle all other events
    }

    void Application::Stop()
    {
        m_Running = false;
    }

    void Application::Run()
    {
        // Program loop here
        while(m_Running)
        {
            // TODO: setup timing

            if (m_Window->ShouldClose())
                this->Stop();

            // Render here


            // Swap front and back buffers
            m_Window->SwapBuffers();

            // Poll and process events
            m_Window->PollEvents();
        }
    }
}

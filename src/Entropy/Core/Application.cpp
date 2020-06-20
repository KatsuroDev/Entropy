#include "Application.h"

#include "../Renderer/Renderer.h"
#include "Logger.h"
#include "Input.h"

namespace Entropy {

    Application* Application::s_Instance = nullptr;

    Application::Application(int width, int height, const char* title)
    {
        Logger::Trace("Hello from the logger! Warming transistors...");
        s_Instance = this;

        m_Window = Window::Create(width, height, title);
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        m_Window->SetVSync(true);

        Renderer::Init();
        //Renderer::SetClearColor(Vector4f(0.0f, 0.39f, 0.65f, 1.0f));
        //Renderer::Clear();
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
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

        // Handle all other events
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        std::stringstream ss;
        ss << "Resized window: (" << m_Window->GetWidth() << "x" << m_Window->GetHeight() << ")";
        Logger::Info(ss.str());
        return false;
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

            // Render here
            m_Window->OnUpdate();
        }
    }
}

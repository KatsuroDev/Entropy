#include "Application.h"

#include "../Renderer/Renderer.h"
#include "Logger.h"
#include "Input.h"

#include <math.h>

#include <GLFW/glfw3.h>

namespace Entropy {

	Application* Application::s_Instance = nullptr;

	Application::Application(int width, int height, const char* title)
	{
		NT_TRACE("Hello from the logger! Warming transistors...");
		s_Instance = this;

		m_Window = Window::Create(width, height, title);
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();
	}

	Application::~Application()
	{
		// Shutdown the renderer
		Renderer::Dispose();

		// Deleting window
		delete m_Window;

		NT_TRACE("Hey! Come back next time.");
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
		NT_INFO(ss.str());
		return false;
	}

	void Application::Stop()
	{
		m_Running = false;
	}

	void Application::Run()
	{
		// Program loop here
		while (m_Running)
		{
			float time = glfwGetTime();
			float sint = abs(sinf(time));
			// Render here
			RenderCommand::SetClearColor(Vector4f(0.0862f * sint, 0.3764f * sint, 0.6549f * sint, 1.0f));
			RenderCommand::Clear();
			m_Window->OnUpdate();

			std::stringstream ss;
			ss << "Time: " << time << "s";
			NT_TRACE(ss.str());
		}
	}
}

#include "Application.h"

#include "Core.h"
#include "Input.h"

#include "../Renderer/Renderer.h"
#include "../Renderer/RenderCommand.h"

#include "../Tools/Colorimetry.h"

#include <cmath>

// Only to get time
#include <GLFW/glfw3.h>

#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"

namespace Entropy {

	Application* Application::s_Instance = nullptr;

	Application::Application(int width, int height, const char* title)
	{
		NT_TRACE("Hello from the logger! Warming transistors...");
		s_Instance = this;

		m_Window = Window::Create(width, height, title);
		m_Window->SetEventCallback(NT_ATTACH_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(true);

		// Setting title to Render API used
		Application::GetWindow().SetTitle(Application::GetWindow().GetTitle() + " - " + RenderingAPI::GetName());

		Renderer::Init();
	}

	Application::~Application()
	{
		// Shutdown the renderer
		Renderer::Dispose();

		NT_TRACE("Hey! Come back next time.");
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(NT_ATTACH_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(NT_ATTACH_EVENT_FN(Application::OnWindowResized));

		// Handle all other events
		if (!e.Handled)
			OnApplicationEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResized(WindowResizeEvent& e)
	{
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

	void Application::Stop()
	{
		m_Running = false;
	}

	void Application::Run()
	{
		OnCreate();

		RenderCommand::SetClearColor(EncodeSRGB(glm::vec4(0.0862f, 0.3764f, 0.6549f, 1.0f)));

		float fStartTime = 0.0f;

		// Program loop here
		while (m_Running)
		{
			RenderCommand::Clear();

			if (Input::IsKeyPressed(KeyCode::Escape))
				Application::Get().GetWindow().SetCursorNormal();

			if (Input::IsMouseButtonPressed(MouseCode::ButtonLeft))
				Application::Get().GetWindow().SetCursorDisabled();

			// Render here
			// Pass in the elapsed time between frames
			float fEndTime = glfwGetTime();
			OnUpdate(fEndTime - fStartTime);
			fStartTime = fEndTime;

			m_Window->OnUpdate();
		}
	}
}

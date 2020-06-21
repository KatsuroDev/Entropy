#include "DefaultWindow.h"

#include "../../Entropy/Core/Input.h"
#include "../../Entropy/Events/ApplicationEvent.h"
#include "../../Entropy/Events/KeyEvent.h"
#include "../../Entropy/Events/MouseEvent.h"

#include "../../Entropy/Renderer/Renderer.h"

#include "../../Platform/OpenGL/OpenGLGraphicsContext.h"

#include "../../Entropy/Core/Logger.h"

namespace Entropy {

	static unsigned int s_WindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		Logger::FATAL(description);
	}

	DefaultWindow::DefaultWindow(unsigned int width, unsigned int height, const char* title)
	{
		Init(width, height, title);
	}

	DefaultWindow::~DefaultWindow()
	{
		Shutdown();
	}

	void DefaultWindow::Init(unsigned int width, unsigned int height, const char* title)
	{
		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;

		if (s_WindowCount == 0)
		{
			if (!glfwInit())
				Logger::FATAL("Could not init GLFW");
			Logger::Info("GLFW has been initialized successfully!");

			glfwSetErrorCallback(GLFWErrorCallback);

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif
		}

		m_Window = glfwCreateWindow((int)width, (int)height, title, nullptr, nullptr);
		++s_WindowCount;

		// Creating the graphics context
		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// -----------------------------------------------------------------------
		// CALLBACKS
		// -----------------------------------------------------------------------
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(static_cast<KeyCode>(keycode));
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void DefaultWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		--s_WindowCount;

		// Cleans up glfw's garbage
		if (s_WindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void DefaultWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void DefaultWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool DefaultWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}

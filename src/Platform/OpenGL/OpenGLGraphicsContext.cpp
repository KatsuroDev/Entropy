#include "OpenGLGraphicsContext.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../Entropy/Core/Logger.h"

namespace Entropy {

	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		if (windowHandle == nullptr)
			Logger::FATAL("Window handle is null");
	}

	void OpenGLGraphicsContext::Init()
	{
		// Need to make the context before init glew
		glfwMakeContextCurrent(m_WindowHandle);

		if (glewInit() != GLEW_OK)
			Logger::FATAL("Could not init glew");
		Logger::Info("Initialized glew successfully!");

		Logger::Info("OpenGL Info:\n");
		std::stringstream ss;
		ss << glGetString(GL_VENDOR) << '\n' << glGetString(GL_RENDERER) << '\n' << glGetString(GL_VERSION) << '\n';
		Logger::Info(ss.str());
	}

	void OpenGLGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}

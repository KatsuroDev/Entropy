#include "OpenGLGraphicsContext.h"

#include "../../Entropy/Core/Core.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Entropy {

	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		if (windowHandle == nullptr)
			NT_FATAL(0, "Window handle is null");
	}

	void OpenGLGraphicsContext::Init()
	{
		// Need to make the context before init glew
		glfwMakeContextCurrent(m_WindowHandle);

		if (glewInit() != GLEW_OK)
			NT_FATAL(0, "Could not init glew");
		NT_INFO("Initialized glew successfully!");

		NT_INFO("OpenGL Info:\n");
		std::stringstream ss;
		ss << glGetString(GL_VENDOR) << '\n' << glGetString(GL_RENDERER) << '\n' << glGetString(GL_VERSION) << '\n';
		NT_INFO(ss.str());
	}

	void OpenGLGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}

#pragma once

#include "../../Entropy/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Entropy {

	class OpenGLGraphicsContext : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

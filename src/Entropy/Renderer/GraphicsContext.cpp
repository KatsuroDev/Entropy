#include "GraphicsContext.h"

#include "../../Entropy/Renderer/Renderer.h"
// Include all supported APIs context
#include "../../Platform/OpenGL/OpenGLGraphicsContext.h"

#include "../../Entropy/Core/Logger.h"

namespace Entropy {

	GraphicsContext* GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::OpenGL: return new OpenGLGraphicsContext((GLFWwindow*)window);
			Logger::Info("Created OpenGL Graphics Context!");
			break;
		case RenderingAPI::API::None:
			Logger::FATAL("Could not create graphics context");
		}
	}
}

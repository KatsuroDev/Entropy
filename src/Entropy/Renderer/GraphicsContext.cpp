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
		case RenderingAPI::API::OpenGL:
			NT_INFO("Created OpenGL Graphics Context!");
			return new OpenGLGraphicsContext((GLFWwindow*)window);
		case RenderingAPI::API::None:
			NT_FATAL("Could not create graphics context");
		}
	}
}

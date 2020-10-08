#include "GraphicsContext.h"

#include "../Renderer/Renderer.h"

// Include all supported APIs context
#include "../../Platform/OpenGL/OpenGLGraphicsContext.h"

namespace Entropy {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::OpenGL:
			NT_INFO("Created OpenGL Graphics Context!");
			return CreateScope<OpenGLGraphicsContext>(static_cast<GLFWwindow*>(window));
		case RenderingAPI::API::None:
			NT_FATAL("Could not create graphics context");
			return nullptr;
		}

		NT_FATAL("Unknown Rendering API");
		return nullptr;
	}
}

#include "Texture.h"

#include "Renderer.h"

// Include all API's textures
#include "../../Platform/OpenGL/OpenGLTexture.h"

namespace Entropy {

	Ref<Texture2D> Texture2D::Create(unsigned int width, unsigned int height)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
			break;
		case RenderingAPI::API::None:
			NT_FATAL("Rendering API not supported");
			return nullptr;
		}

		NT_FATAL("Unknown Rendering API");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(filepath);
			break;
		case RenderingAPI::API::None:
			NT_FATAL("Rendering API not supported");
			return nullptr;
		}

		NT_FATAL("Unknown Rendering API");
		return nullptr;
	}
}

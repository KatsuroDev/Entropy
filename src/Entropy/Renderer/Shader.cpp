#include "Shader.h"

#include "Renderer.h"

// Include all API's shader
#include "../../Platform/OpenGL/OpenGLShader.h"

#include "../../Entropy/Core/Logger.h"

namespace Entropy {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::OpenGL:
			return new OpenGLShader(filepath);
			break;
		case RenderingAPI::API::None:
			NT_FATAL("Rendering API not supported");
			return nullptr;
		}

		return nullptr;
	}

	Shader* Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::API::OpenGL:
			return new OpenGLShader(name, vertexSource, fragmentSource);
			break;
		case RenderingAPI::API::None:
			NT_FATAL("Rendering API not supported");
			return nullptr;
		}

		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, Shader* shader)
	{
		if (Exists(name))
			NT_FATAL("Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(Shader* shader)
	{
		const std::string& name = shader->GetName();
		Add(name, shader);
	}

	Shader* ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Shader* ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Shader* ShaderLibrary::Get(const std::string& name)
	{
		if (!Exists(name))
			NT_FATAL("Shader not found!");

		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}

#include "Renderer.h"

#include "RenderCommand.h"

namespace Entropy {

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Dispose()
	{
	}

	void Renderer::Draw(const Ref<Shader>& shader, const Ref<VertexArray>& va, const glm::mat4& transform, const Camera& camera)
	{
		shader->Attach();
		// camera uniforms
		shader->SetFloat3("u_CameraPosition", camera.GetPosition());
		shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		shader->SetMat4("u_Model", transform);

		if (va != nullptr)
		{
			va->Attach();
			RenderCommand::Draw(va);
		}
		else
		{
			NT_WARN("A mesh was not rendered: VAO was nullptr");
		}
	}

	void Renderer::DrawInstanced(const Ref<Shader>& shader, const Ref<VertexArray>& va, const glm::mat4& transform, const Camera& camera, unsigned int repeatCount)
	{
		shader->Attach();
		// camera uniforms
		shader->SetFloat3("u_CameraPosition", camera.GetPosition());
		shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		shader->SetMat4("u_Model", transform);

		if (va != nullptr)
		{
			va->Attach();
			RenderCommand::DrawInstanced(va, repeatCount);
		}
		else
		{
			NT_WARN("A mesh was not rendered: VAO was nullptr");
		}
	}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}

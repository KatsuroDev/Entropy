#include "Renderer.h"

#include "../Core/Logger.h"

namespace Entropy {

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Dispose()
	{
		NT_INFO("Disposed of renderer's ressources");
	}

	void Renderer::Draw(Shader* shader, VertexArray* vertexArray, const glm::mat4& transform, const Camera& camera)
	{
		shader->Attach();
		shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		shader->SetMat4("u_Transform", transform);

		vertexArray->Attach();
		RenderCommand::Draw(vertexArray);
	}

	void Renderer::DrawInstanced(Shader* shader, VertexArray* vertexArray, const glm::mat4& transform, const Camera& camera, unsigned int repeatCount)
	{
		shader->Attach();
		shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		shader->SetMat4("u_Transform", transform);

		vertexArray->Attach();
		RenderCommand::DrawInstanced(vertexArray, repeatCount);
	}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}

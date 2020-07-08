#include "Renderer.h"

#include "../Core/Logger.h"

#include "RenderCommand.h"

namespace Entropy {

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Dispose()
	{

	}

	void Renderer::Draw(Shader* shader, VertexArray* va, const glm::mat4& transform, const Camera& camera)
	{
		shader->Attach();
		// camera uniforms
		shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		shader->SetMat4("u_Transform", transform);

		va->Attach();
		RenderCommand::Draw(va);
	}

	void Renderer::DrawInstanced(Shader* shader, VertexArray* va, const glm::mat4& transform, const Camera& camera, unsigned int repeatCount)
	{
		shader->Attach();
		// camera uniforms
		shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		shader->SetMat4("u_Transform", transform);

		va->Attach();
		RenderCommand::DrawInstanced(va, repeatCount);
	}

	void Renderer::Draw(Shader* shader, const Mesh& mesh, const glm::mat4& transform, const Camera& camera)
	{
		shader->Attach();
		// camera uniforms
		shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		shader->SetMat4("u_Transform", transform);

		// per mesh uniforms
		shader->SetFloat("u_ShineDamper", mesh.GetShineDamper());
		shader->SetFloat("u_Reflectivity", mesh.GetReflectivity());

		VertexArray* va = mesh.GetVertexArray();
		va->Attach();
		RenderCommand::Draw(va);
	}

	void Renderer::DrawInstanced(Shader* shader, const Mesh& mesh, const glm::mat4& transform, const Camera& camera, unsigned int repeatCount)
	{
		shader->Attach();
		// camera uniforms
		shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		shader->SetMat4("u_Transform", transform);

		// per mesh uniforms
		shader->SetFloat("u_ShineDamper", mesh.GetShineDamper());
		shader->SetFloat("u_Reflectivity", mesh.GetReflectivity());

		VertexArray* va = mesh.GetVertexArray();
		va->Attach();
		RenderCommand::DrawInstanced(va, repeatCount);
	}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}

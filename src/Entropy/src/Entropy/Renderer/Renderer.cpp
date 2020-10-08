#include "Renderer.h"

#include "../Core/Core.h"
#include <GL/glm/glm.hpp>

namespace Entropy {

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec3 Normal;
	};

	struct RendererData
	{
		static const uint32_t MaxVertices = 80000;

		Ref<VertexArray> VertexArray;
		Ref<VertexBuffer> VertexBuffer;
	};

	static RendererData s_Data;
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	// Creates the vertex array
	void Renderer::Init()
	{
		RenderCommand::Init();

		s_Data.VertexArray = VertexArray::Create();

		s_Data.VertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(Vertex));
		s_Data.VertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float3, "a_Normal" }
		});
		s_Data.VertexArray->AddVertexBuffer(s_Data.VertexBuffer);
	}

	void Renderer::Dispose()
	{

	}

	void Renderer::BeginBatch(const Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		s_SceneData->CameraPosition = camera.GetPosition(); // TODO: get position from matrix
	}

	void Renderer::EndBatch()
	{
		// TODO: Draw calls here
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& va, const glm::mat4& transform)
	{
		shader->Attach();
		shader->SetFloat3("u_CameraPosition", s_SceneData->CameraPosition);
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Model", transform);

		// TODO: append this to batch
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

	int Renderer::GetTextureSlotsCount()
	{
		RenderCommand::GetTextureSlotsCount();
	}

	const char* Renderer::GetSpecification()
	{
		return RenderCommand::GetSpecification();
	}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}

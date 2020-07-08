#pragma once

#include "RenderingAPI.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

namespace Entropy {

	class Renderer
	{
	public:
		static void Init();
		static void Dispose();

		static void OnWindowResize(unsigned int width, unsigned int height);

		static void Draw(Shader* shader, VertexArray* va, const glm::mat4& transform, const Camera& camera);
		static void DrawInstanced(Shader* shader, VertexArray* va, const glm::mat4& transform, const Camera& camera, unsigned int repeatCount);

		static void Draw(Shader* shader, const Mesh& mesh, const glm::mat4& transform, const Camera& camera);
		static void DrawInstanced(Shader* shader, const Mesh& mesh, const glm::mat4& transform, const Camera& camera, unsigned int repeatCount);

		static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
	};
}

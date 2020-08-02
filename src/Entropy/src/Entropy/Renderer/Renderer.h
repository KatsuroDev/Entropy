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

		// TODO: instead of these draw calls, have a submit method that puts all this in one VAO
		static void Draw(const Ref<Shader>& shader, const Ref<VertexArray>& va, const glm::mat4& transform, const Camera& camera);
		static void DrawInstanced(const Ref<Shader>& shader, const Ref<VertexArray>& va, const glm::mat4& transform, const Camera& camera, unsigned int repeatCount);

		static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }
	};
}

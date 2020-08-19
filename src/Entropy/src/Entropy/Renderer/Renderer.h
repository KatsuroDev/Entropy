#pragma once

#include "RenderCommand.h"
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

		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& va, const glm::mat4& transform = glm::mat4(1.0f));

		static RenderingAPI::API GetAPI() { return RenderingAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			glm::vec3 CameraPosition;
		};

		static Scope<SceneData> s_SceneData;
	};
}

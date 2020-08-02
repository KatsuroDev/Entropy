#pragma once

#include "../Core/Core.h"

#include "RenderingAPI.h"

namespace Entropy {

	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RenderingAPI->Init();
			NT_INFO("Initialized the rendering API");
		}

		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
		{
			s_RenderingAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_RenderingAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_RenderingAPI->Clear();
		}

		static void Draw(const Ref<VertexArray>& vertexArray, unsigned int indexCount = 0)
		{
			s_RenderingAPI->Draw(vertexArray, indexCount);
		}

		static void DrawInstanced(const Ref<VertexArray>& vertexArray, unsigned int repeatCount, unsigned int indexCount = 0)
		{
			s_RenderingAPI->DrawInstanced(vertexArray, repeatCount, indexCount);
		}

	private:
		static Scope<RenderingAPI> s_RenderingAPI;
	};
}

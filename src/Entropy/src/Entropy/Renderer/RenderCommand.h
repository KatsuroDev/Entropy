#pragma once

#include "RenderingAPI.h"

#include "../Core/Logger.h"

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

		static void Draw(VertexArray* vertexArray, unsigned int indexCount = 0)
		{
			s_RenderingAPI->Draw(vertexArray, indexCount);
		}

		static void DrawInstanced(VertexArray* vertexArray, unsigned int repeatCount, unsigned int indexCount = 0)
		{
			s_RenderingAPI->DrawInstanced(vertexArray, repeatCount, indexCount);
		}

	private:
		static RenderingAPI* s_RenderingAPI;
	};
}

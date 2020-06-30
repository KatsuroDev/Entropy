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

		static void Draw(VertexArray* vertexArray, unsigned int count = 0)
		{
			s_RenderingAPI->Draw(vertexArray, count);
		}

	private:
		static RenderingAPI* s_RenderingAPI;
	};
}

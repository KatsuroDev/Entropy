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
			std::stringstream ss;
			ss << "RENDERER: Resized viewport to (" << width << "x" << height << ")";
			NT_TRACE(ss.str());
		}

		static void SetClearColor(const Vector4f& color)
		{
			s_RenderingAPI->SetClearColor(color);
			std::stringstream ss;
			ss << "RENDERER: Set clear color to (" << color.X << ", " << color.Y << ", " << color.Z << ", " << color.W << ")";
			NT_TRACE(ss.str());
		}

		static void Clear()
		{
			s_RenderingAPI->Clear();
			NT_TRACE("RENDERER: Cleared");
		}

		static void DrawPending(const VertexArray& vertexArray, unsigned int count = 0)
		{
			s_RenderingAPI->DrawPending(vertexArray, count);
			NT_TRACE("RENDERER: Drawn batch");
		}

	private:
		static RenderingAPI* s_RenderingAPI;
	};
}

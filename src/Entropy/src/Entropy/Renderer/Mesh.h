#pragma once

#include "Renderer.h"

namespace Entropy {

	class Mesh
	{
	public:
		Mesh(const BufferLayout& layout);
		~Mesh();

	private:
		VertexArray* m_VertexArray;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
	};
}

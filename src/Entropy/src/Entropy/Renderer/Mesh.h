#pragma once

#include "Renderer.h"

namespace Entropy {

	class Mesh
	{
	public:
		Mesh(const char* filepath);
		~Mesh();

		VertexArray* GetVertexArray() const { return m_VertexArray; }
		VertexBuffer* GetVertexBuffer() const { return m_VertexBuffer; }
		IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		bool LoadFromFile(const char* filepath);

	private:
		VertexArray* m_VertexArray;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;

		bool m_SmoothShadingEnabled;
	};
}

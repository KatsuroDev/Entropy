#pragma once

#include "../Core/Core.h"

#include "VertexArray.h"

namespace Entropy {

	class Mesh
	{
	public:
		/// Shine damper changes how wide the specular is going to be
		/// Reflecitvity changes how reflective the surface will be
		Mesh();
		~Mesh();

		std::shared_ptr<VertexArray> GetVertexArray() const { return m_VertexArray; }
		std::shared_ptr<VertexBuffer> GetVertexBuffer() const { return m_VertexBuffer; }
		std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }

		// Smooth lighting enabled by default
		// TODO: support sharp edges and sharp angle threshold detector
		bool LoadOBJFromFile(const char* filepath);

		void GenerateTerrain(unsigned int scale, unsigned int seed);

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}

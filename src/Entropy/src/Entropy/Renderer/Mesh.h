#pragma once

#include "../Core/Core.h"

#include "VertexArray.h"

namespace Entropy {

	class Mesh
	{
	public:
		Mesh();

		const Ref<VertexArray>& GetVertexArray() const { return m_VertexArray; }
		const Ref<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		// Smooth lighting enabled by default
		// TODO: support sharp edges and sharp angle threshold detector
		// use Assimp
		bool LoadOBJFromFile(const char* filepath);

		void GenerateUnitCube();
		void GenerateTerrain(unsigned int scale, unsigned int seed);

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}

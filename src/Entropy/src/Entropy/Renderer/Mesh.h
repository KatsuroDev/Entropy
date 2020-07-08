#pragma once

#include "VertexArray.h"

namespace Entropy {

	class Mesh
	{
	public:
		/// Shine damper changes how wide the specular is going to be
		/// Reflecitvity changes how reflective the surface will be
		Mesh();
		~Mesh();

		VertexArray* GetVertexArray() const { return m_VertexArray; }
		VertexBuffer* GetVertexBuffer() const { return m_VertexBuffer; }
		IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

		float GetShineDamper() const { return m_ShineDamper; }
		float GetReflectivity() const { return m_Reflectivity; }
		void SetShineDamper(float shineDamper) { m_ShineDamper = shineDamper; }
		void SetReflectivity(float reflectivity) { m_Reflectivity = reflectivity; }

		bool LoadOBJFromFile(const char* filepath);

	private:
		VertexArray* m_VertexArray = nullptr;
		VertexBuffer* m_VertexBuffer = nullptr;
		IndexBuffer* m_IndexBuffer = nullptr;

		float m_ShineDamper;
		float m_Reflectivity;
	};
}

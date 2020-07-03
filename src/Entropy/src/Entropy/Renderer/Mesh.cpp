#include "Mesh.h"

namespace Entropy {

	Mesh::Mesh(const BufferLayout& layout)
	{
		m_VertexArray = VertexArray::Create();

		// TODO: load these from file
		float vertices[1] = {

		};

		unsigned int indices[1] = {

		};

		m_VertexBuffer = Entropy::VertexBuffer::Create(vertices, sizeof(vertices));
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_IndexBuffer = Entropy::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}

	Mesh::~Mesh()
	{
		delete m_IndexBuffer;
		delete m_VertexBuffer;
		delete m_VertexArray;
	}
}

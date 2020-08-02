#include "Mesh.h"

#include "../Tools/Noise.h"

#include <fstream>
#include <vector>

#include <GL/glm/glm.hpp>

namespace Entropy {

	Mesh::Mesh()
		// TODO: make proper materials
		: m_VertexArray(0), m_VertexBuffer(0), m_IndexBuffer(0)
	{
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::GenerateTerrain(unsigned int scale, unsigned int seed)
	{
		// We want the number of vertices, not grids, therefore +1
		unsigned int size = scale + 1;
		size_t vertexBufferCount = (size_t)size * size * 8;
		float* vertexBuffer = new float[vertexBufferCount];

		std::vector<unsigned int> indexBuffer;

		// filling the vertex buffer
		for (int y = 0; y < size; y++)
			for (int x = 0; x < size; x++)
			{
				int pos = 8 * (y * size + x);
				float height0 = rand() % 8 / 256.0f;
				float height1 = rand() % 8 / 256.0f;
				float height2 = rand() % 8 / 256.0f;

				const float centerOffset = (size - 1) * 0.5f;

				// position
				vertexBuffer[pos + 0] = x - centerOffset;
				vertexBuffer[pos + 1] = height0;
				vertexBuffer[pos + 2] = y - centerOffset;

				// texCoord
				vertexBuffer[pos + 3] = x;
				vertexBuffer[pos + 4] = y;

				// normal
				glm::vec3 line1(glm::vec3(x, height1, y + 1) - glm::vec3(x, height0, y));
				glm::vec3 line2(glm::vec3(x + 1, height2, y) - glm::vec3(x, height0, y));
				glm::vec3 normal = glm::normalize(glm::cross(line1, line2));

				vertexBuffer[pos + 5] = normal.x;
				vertexBuffer[pos + 6] = normal.y;
				vertexBuffer[pos + 7] = normal.z;
			}

		// filling the index buffer
		for (int y = 0; y < size - 1; y++)
			for (int x = 0; x < size - 1; x++)
			{
				// face #1
				indexBuffer.push_back((y + 0) * size + (x + 0));
				indexBuffer.push_back((y + 1) * size + (x + 0));
				indexBuffer.push_back((y + 0) * size + (x + 1));

				// face #2
				indexBuffer.push_back((y + 1) * size + (x + 1));
				indexBuffer.push_back((y + 0) * size + (x + 1));
				indexBuffer.push_back((y + 1) * size + (x + 0));
			}

		// Init buffers
		m_VertexArray = VertexArray::Create();

		// Init default layout
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float3, "a_Normal" }
		};

		// Takes size in bytes
		m_VertexBuffer = VertexBuffer::Create(vertexBuffer, vertexBufferCount * sizeof(float));
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		// Takes index count
		m_IndexBuffer = IndexBuffer::Create(&indexBuffer[0], indexBuffer.size());
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		delete[] vertexBuffer;
	}

	void Tokenize(const std::string& str, const char delim, std::vector<std::string>& out)
	{
		size_t start;
		size_t end = 0;

		out.clear();
		while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
		{
			end = str.find(delim, start);
			out.push_back(str.substr(start, end - start));
		}
	}

	void SplitIndexData(const std::string& data, unsigned int indices[])
	{
		std::string sIndex = "";
		int count = 0;
		for (unsigned int i = 0; i <= data.length(); i++)
		{
			if (data[i] != '/')
			{
				// Char is numerical
				sIndex += data[i];
			}
			else if (data[i] == '/')
			{
				if (sIndex.length() != 0)
				{
					indices[count] = std::stoul(sIndex);
				}
				else
				{
					indices[count] = 0;
				}

				count++;
				sIndex = "";
			}
		}

		indices[count] = std::stoul(sIndex);
	}

	bool Mesh::LoadOBJFromFile(const char* filepath)
	{
		std::ifstream in(filepath, std::ios::in);
		if (!in.is_open())
			return false;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> textures;
		std::vector<glm::vec3> normals;

		std::string line;
		std::vector<std::string> tokens;

		bool smoothShaded = true;

		// LOADING SECTION -------------------------------------------
		while (true)
		{
			std::getline(in, line);
			Tokenize(line, ' ', tokens);

			// Starts with v
			if (line.substr(0, 2) == "v ")
			{
				glm::vec3 vertex;
				vertex.x = std::stof(tokens[1]);
				vertex.y = std::stof(tokens[2]);
				vertex.z = std::stof(tokens[3]);
				positions.push_back(vertex);
			}
			// Starts with vt
			else if (line.substr(0, 2) == "vt")
			{
				glm::vec2 texCoord;
				texCoord.x = std::stof(tokens[1]);
				texCoord.y = std::stof(tokens[2]);
				textures.push_back(texCoord);
			}
			// Starts with vn
			else if (line.substr(0, 2) == "vn")
			{
				glm::vec3 normal;
				normal.x = std::stof(tokens[1]);
				normal.y = std::stof(tokens[2]);
				normal.z = std::stof(tokens[3]);
				normals.push_back(normal);
			}
			else if (line.substr(0, 2) == "s ")
			{
				// smooth shading flag
				if (line.substr(2, 3) == "off")
				{
					smoothShaded = false;
					NT_INFO("Model has smooth shading disabled");
				}
			}
			else if (line.substr(0, 2) == "f ")
				break;
		}

		// COMPUTING SECTION -------------------------------------------
		size_t vertexBufferCount = positions.size() * 8;
		float* vertexBuffer = new float[vertexBufferCount];
		std::vector<unsigned int> indexBuffer;

		// looping through all faces
		while (!in.eof())
		{
			// executes 2 times
			if (line.substr(0, 2) == "f ")
			{
				// Contains data about how to link position, texture coords and normals
				unsigned int vertex0[3]; // pos_ptr // tex_ptr // norm_ptr
				unsigned int vertex1[3];
				unsigned int vertex2[3];

				SplitIndexData(tokens[1], vertex0);
				SplitIndexData(tokens[2], vertex1);
				SplitIndexData(tokens[3], vertex2);

				unsigned int v0 = vertex0[0] - 1; unsigned int v1 = vertex1[0] - 1; unsigned int v2 = vertex2[0] - 1;
				unsigned int t0 = vertex0[1] - 1; unsigned int t1 = vertex1[1] - 1; unsigned int t2 = vertex2[1] - 1;
				unsigned int n0 = vertex0[2] - 1; unsigned int n1 = vertex1[2] - 1; unsigned int n2 = vertex2[2] - 1;

				// Construct triangle
				vertexBuffer[8 * v0] = positions[v0].x;
				vertexBuffer[8 * v0 + 1] = positions[v0].y;
				vertexBuffer[8 * v0 + 2] = positions[v0].z;
				vertexBuffer[8 * v0 + 3] = 0.0f;
				vertexBuffer[8 * v0 + 4] = 0.0f;
				vertexBuffer[8 * v0 + 5] = normals[n0].x;
				vertexBuffer[8 * v0 + 6] = normals[n0].y;
				vertexBuffer[8 * v0 + 7] = normals[n0].z;

				vertexBuffer[8 * v1] = positions[v1].x;
				vertexBuffer[8 * v1 + 1] = positions[v1].y;
				vertexBuffer[8 * v1 + 2] = positions[v1].z;
				vertexBuffer[8 * v1 + 3] = 0.0f;
				vertexBuffer[8 * v1 + 4] = 0.0f;
				vertexBuffer[8 * v1 + 5] = normals[n1].x;
				vertexBuffer[8 * v1 + 6] = normals[n1].y;
				vertexBuffer[8 * v1 + 7] = normals[n1].z;

				vertexBuffer[8 * v2] = positions[v2].x;
				vertexBuffer[8 * v2 + 1] = positions[v2].y;
				vertexBuffer[8 * v2 + 2] = positions[v2].z;
				vertexBuffer[8 * v2 + 3] = 0.0f;
				vertexBuffer[8 * v2 + 4] = 0.0f;
				vertexBuffer[8 * v2 + 5] = normals[n2].x;
				vertexBuffer[8 * v2 + 6] = normals[n2].y;
				vertexBuffer[8 * v2 + 7] = normals[n2].z;

				indexBuffer.push_back(v0);
				indexBuffer.push_back(v1);
				indexBuffer.push_back(v2);
			}

			// Reading after because we already read the file once
			std::getline(in, line);
			Tokenize(line, ' ', tokens);
		}

		in.close();

		// Init buffers
		m_VertexArray = VertexArray::Create();

		// Init default layout
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float3, "a_Normal" }
		};

		// Takes size in bytes
		m_VertexBuffer = VertexBuffer::Create(vertexBuffer, vertexBufferCount * sizeof(float));
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		// Takes index count
		m_IndexBuffer = IndexBuffer::Create(&indexBuffer[0], indexBuffer.size());
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		delete[] vertexBuffer;

		return true;
	}
}

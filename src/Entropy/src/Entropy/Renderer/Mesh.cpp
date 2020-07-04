#include "Mesh.h"

#include <fstream>

namespace Entropy {

	Mesh::Mesh(const char* filepath)
	{
		if (LoadFromFile(filepath))
		{
			std::stringstream ss;
			ss << "Successfully imported '" << filepath << "'";
			NT_INFO(ss.str());
		}
		else
		{
			std::stringstream ss;
			ss << "Could not read from file '" << filepath << "'";
			NT_ERROR(ss.str());
		}
	}

	Mesh::~Mesh()
	{
		delete m_IndexBuffer;
		delete m_VertexBuffer;
		delete m_VertexArray;
	}

	// Works for Blender objs
	bool Mesh::LoadFromFile(const char* filepath)
	{
		std::ifstream ifs(filepath, std::ios::in);
		if (ifs)
		{
			struct Triangle
			{
				glm::vec3 positions[3];
			};

			std::vector<Triangle> triangles;

			// Contains all vertex positions
			std::vector<glm::vec3> positions;

			std::string line;
			while (!ifs.eof())
			{
				char header = ifs.peek();
				if (header == 'v')
				{
					// Reading vertex position
					glm::vec3 pos;
					ifs >> header >> pos.x >> pos.y >> pos.z;

					// Position
					positions.push_back(pos);
				}
				else if (header == 'f')
				{
					// Crashed if string contains '/'
					// Reading face information
					unsigned int triIndex[3];
					ifs >> header >> triIndex[0] >> triIndex[1] >> triIndex[2];

					Triangle tri;
					tri.positions[0] = positions[triIndex[0] - 1];
					tri.positions[1] = positions[triIndex[1] - 1];
					tri.positions[2] = positions[triIndex[2] - 1];
					triangles.push_back(tri);
				}
				else if (header == 's')
				{
					std::string shadingType;
					ifs >> header >> shadingType;
					if (shadingType == "off")
					{
						m_SmoothShadingEnabled = false;
						NT_INFO("Model has smooth shading disabled");
					}
					else if (shadingType == "on")
					{
						m_SmoothShadingEnabled = true;
						NT_INFO("Model has smooth shading enabled");
					}
					else
					{
						// TODO: allow it to be turned on be default
						// Turn it off be default if not defined
						m_SmoothShadingEnabled = false;
						NT_WARN("Model has undefined shading behaviour, default will be applied");
					}
				}
				else
				{
					// If symbol not supported, skip line
					std::string line;
					std::getline(ifs, line);
				}
			}

			std::vector<float> vertices;
			std::vector<unsigned int> indices;

			unsigned int index = 0;
			// Loop through all triangles
			for (Triangle tri : triangles)
			{
				if (!m_SmoothShadingEnabled)
				{
					// Compute normals
					glm::vec3 line1(glm::vec3(tri.positions[1].x, tri.positions[1].y, tri.positions[1].z) - glm::vec3(tri.positions[0].x, tri.positions[0].y, tri.positions[0].z));
					glm::vec3 line2(glm::vec3(tri.positions[2].x, tri.positions[2].y, tri.positions[2].z) - glm::vec3(tri.positions[0].x, tri.positions[0].y, tri.positions[0].z));
					glm::vec3 normal = glm::normalize(glm::cross(line1, line2));

					// For each vertex
					for (unsigned int i = 0; i < 3; i++)
					{
						// positions
						vertices.push_back(tri.positions[i].x);
						vertices.push_back(tri.positions[i].y);
						vertices.push_back(tri.positions[i].z);

						// colors // hard coded white
						vertices.push_back(0.2f);
						vertices.push_back(0.2f);
						vertices.push_back(0.2f);

						// normals
						vertices.push_back(normal.x);
						vertices.push_back(normal.y);
						vertices.push_back(normal.z);

						// In that case, the index array is useless since all vertices are duplicated
						indices.push_back(index++);
					}
				}
				else
				{

				}
			}

			// Init buffers
			m_VertexArray = VertexArray::Create();

			// Init default layout
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float3, "a_MaterialDiffuseColor" },
				{ ShaderDataType::Float3, "a_Normal" }
			};

			// Takes size in bytes
			// m_VertexBuffer = VertexBuffer::Create(&vertices[0], );
			m_VertexBuffer = VertexBuffer::Create(&vertices[0], vertices.size() * sizeof(float));
			m_VertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(m_VertexBuffer);

			// Takes index count
			m_IndexBuffer = IndexBuffer::Create(&indices[0], indices.size());
			m_VertexArray->SetIndexBuffer(m_IndexBuffer);

			return true;
		}

		ifs.close();

		return false;
	}
}

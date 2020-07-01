// This is our game using Entropy Engine
// To be seperated into a seperated new project
// 1. #include "Entropy.h"
// 2. Create a game class that inherits from Entropy::Application
// 3. Call Entropy::CreateApplication(width, height, title) that returns an Entropy::Application*
// You're set!

#include "Entropy.h"

class Game : public Entropy::Application
{
public:
	Game(int width, int height, const char* title)
		: Application(width, height, title), m_CameraController()
	{
		// Vao
		m_VertexArray = Entropy::VertexArray::Create();

		// Vbo
		m_VertexBuffer = Entropy::VertexBuffer::Create(vertices, sizeof(vertices));
		Entropy::BufferLayout layout = {
			{ Entropy::ShaderDataType::Float3, "a_Position" },
			{ Entropy::ShaderDataType::Float4, "a_Color" }
		};
        m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		// Ibo
		unsigned int indices[6] = { 0, 1, 2,   2, 3, 0 };
		m_IndexBuffer = Entropy::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		// Shader
#ifdef _WIN32
		// Visual studio project
		m_Shader = Entropy::Shader::Create("assets/shaders/default.glsl");
#else
		// For building on makefiles
		m_Shader = Entropy::Shader::Create("../assets/shaders/default.glsl");
#endif
	}

	~Game()
	{
		delete m_VertexArray;
		delete m_VertexBuffer;
		delete m_IndexBuffer;
		delete m_Shader;
	}

	virtual void OnUpdate(float elapsedTime) override
	{
		m_CameraController.OnUpdate(elapsedTime);

		// Gamma correction encoding
		Entropy::RenderCommand::SetClearColor(Entropy::EncodeSRGB(glm::vec4(0.0862f, 0.3764f, 0.6549f, 1.0f)));

		// Draw call in this function
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -2.0f));
		transform = glm::rotate(transform, glm::radians(10.0f * elapsedTime), glm::vec3(0.0f, 0.0f, 1.0f));

		Entropy::Renderer::DrawBatch(m_Shader, m_VertexArray, transform, m_CameraController.GetCamera());
	}

	virtual void OnApplicationEvent(Entropy::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Entropy::VertexArray* m_VertexArray;
	Entropy::VertexBuffer* m_VertexBuffer;
	Entropy::IndexBuffer* m_IndexBuffer;
	Entropy::Shader* m_Shader;

	Entropy::CameraController m_CameraController;

	// Geometry data
	float vertices[4 * 7] = {
		// position 		   color 
		-0.5f, -0.5f,  0.0f,   1.0f, 0.0f,  0.0f, 1.0f, // Bottom left
		 0.5f, -0.5f,  0.0f,   0.0f, 1.0f,  0.0f, 1.0f, // Bottom right
		 0.5f,  0.5f,  0.0f,   1.0f, 1.0f,  0.0f, 1.0f, // Top right
		-0.5f,  0.5f,  0.0f,   1.0f, 0.0f,  1.0f, 1.0f  // Top left
	};
};

Entropy::Application* Entropy::CreateApplication()
{
	return new Game(1024, 720, "Entropy Engine Demo");
}

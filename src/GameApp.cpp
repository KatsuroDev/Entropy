// This is our game using Entropy Engine
// To be seperated into a seperated new project
// 1. #include "Entropy.h"
// 2. Create a game class that inherits from Entropy::Application
// 3. Call Entropy::CreateApplication(width, height, title) that returns an Entropy::Application*
// You're set!

#include "Entropy/Entropy.h"

#include <iomanip>

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
			{ Entropy::ShaderDataType::Float3, "a_MaterialDiffuseColor" },
			{ Entropy::ShaderDataType::Float3, "a_Normal" }
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		m_IndexBuffer = Entropy::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		// Shader
#ifdef _WIN32
        m_Shader = Entropy::Shader::Create("src/assets/shaders/default.glsl");
#else
        m_Shader = Entropy::Shader::Create("../src/assets/shaders/default.glsl");
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
		Entropy::RenderCommand::SetClearColor(Entropy::EncodeSRGB(glm::vec4(0.0862f, 0.3764f, 0.6549f, 1.0f) * sinf(0.1f * elapsedTime)));

		// Changing the light over time
		//float brightness = glm::length(m_PointLightColor);
		//m_PointLightColor = glm::normalize(glm::vec3(
		//	abs(sinf(elapsedTime * 0.5f)),
		//	abs(cosf(elapsedTime * 1.78f)),
		//	abs(cosf(elapsedTime * 0.44f)))
		//) * brightness;

		// Moving the light over time
		//m_PointLightPosition.x = 2.0f * sinf(elapsedTime);
		//m_PointLightPosition.z = 2.0f * cosf(elapsedTime);

		// Attaching uniforms
		m_Shader->Attach();
		m_Shader->SetFloat3("u_AmbiantLightColor", m_AmbiantLightColor);
		m_Shader->SetFloat3("u_PointLightPosition", m_PointLightPosition);
		m_Shader->SetFloat3("u_PointLightColor", m_PointLightColor);
		m_Shader->SetFloat3("u_CameraPosition", m_CameraController.GetCamera().GetPosition());

		// Draw call
		Entropy::Renderer::Draw(m_Shader, m_VertexArray, modelTransform, m_CameraController.GetCamera());

		// Changing app title
		/*static std::string appTitle = Application::GetWindow().GetTitle();
		std::stringstream ss;
		ss << appTitle << std::setprecision(2) << std::fixed << " | Position: x" <<
			m_CameraController.GetCamera().GetPosition().x << ", y" <<
			m_CameraController.GetCamera().GetPosition().y << ", z" <<
			m_CameraController.GetCamera().GetPosition().z << " | Velocity: x" <<
			m_CameraController.GetCamera().GetVelocity().x << ", y" <<
			m_CameraController.GetCamera().GetVelocity().y << ", z" <<
			m_CameraController.GetCamera().GetVelocity().z << " (" <<
			glm::length(m_CameraController.GetCamera().GetVelocity()) << "m/s^2)" << " | Pitch: " <<
			m_CameraController.GetCamera().GetPitch() << ", Yaw: " <<
			m_CameraController.GetCamera().GetYaw();

		Application::GetWindow().SetTitle(ss.str());*/
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

	// Model transforms
	glm::mat4 modelTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));

	// Lights
	glm::vec3 m_AmbiantLightColor = glm::vec3(0.0f, 0.08f, 0.2f);
	glm::vec3 m_PointLightPosition = glm::vec3(-2.0f, 2.0f, 3.0f);
	float power = 0.8f;
	glm::vec3 m_PointLightColor = glm::vec3(1.0f, 0.9f, 0.8f) * power;

	// Camera controller
	Entropy::CameraController m_CameraController;

	// Geometry data

#define PLANE

#ifdef PLANE
	float vertices[4 * 9] = {
		// position            color               normal
		 10.0f,  0.0f, -10.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f, // Front bottom right
		-10.0f,  0.0f, -10.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f, // Front bottom left
		-10.0f,  0.0f,  10.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f, // Back bottom left
		 10.0f,  0.0f,  10.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f  // Back bottom right
	};

	unsigned int indices[6] = {
		1,  2,  0,   3,  0,  2
	};
#endif
#ifdef CUBE
	float vertices[24 * 9] = {
		// position            color               normal
		// front																						
		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f, // Front bottom left		// 0
		 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f, // Front bottom right	// 1
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f, // Front top right		// 2
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f, // Front top left		// 3
		// left						 
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, // Back bottom left		// 4
		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, // Front bottom left		// 5
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, // Front top left		// 6
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f, // Back top left			// 7
		// back				   		   
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f, // Back bottom right		// 8
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f, // Back bottom left		// 9
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f, // Back top left			// 10
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, -1.0f, // Back top right		// 11
		// right					
		 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f, // Front bottom right	// 12
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f, // Back bottom right		// 13
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f, // Back top right		// 14
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f, // Front top right		// 15
		// bottom					 
		 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f, // Front bottom right	// 16
		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f, // Front bottom left		// 17
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f, // Back bottom left		// 18
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f, -1.0f,  0.0f, // Back bottom right		// 19
		// top						
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f, // Back top right		// 20
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f, // Back top left			// 21
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f, // Front top left		// 22
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f  // Front top right		// 23
	};

	// Ibo

	unsigned int indices[36] = {
		// front
		1,  2,  0,   3,  0,  2,
		// left
		5,  6,  4,   7,  4,  6,
		// back
		9,  10, 8,   11, 8,  10,
		// right
		13, 14, 12,  15, 12, 14,
		// bottom
		17, 18, 16,  19, 16, 18,
		// top
		21, 22, 20,  23, 20, 22
	};
#endif
};

Entropy::Application* Entropy::CreateApplication()
{
	return new Game(1024, 720, "Entropy Engine Demo");
}

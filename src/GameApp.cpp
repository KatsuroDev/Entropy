// This is our game using Entropy Engine
// To be seperated into a seperated new project
// 1. #include "Entropy.h"
// 2. Create a game class that inherits from Entropy::Application
// 3. Call Entropy::CreateApplication(width, height, title) that returns an Entropy::Application*
// You're set!

#include "Entropy/Entropy.h"

class Game : public Entropy::Application
{
public:
	Game(int width, int height, const char* title)
		: Application(width, height, title), m_CameraController()
	{
		m_CameraController.GetCamera().SetPosition(glm::vec3(0.0f, 1.0f, 1.0f));

		// Shader
#ifdef NT_PLATFORM_WINDOWS
		m_Shader = Entropy::Shader::Create("assets/shaders/default.glsl");
#else
		m_Shader = Entropy::Shader::Create("../assets/shaders/default.glsl");
#endif
	}

	~Game()
	{
		delete m_Shader;
	}

	virtual void OnUpdate(float elapsedTime) override
	{
		m_CameraController.OnUpdate(elapsedTime);

		// Gamma correction encoding
		Entropy::RenderCommand::SetClearColor(Entropy::EncodeSRGB(glm::vec4(0.0862f, 0.3764f, 0.6549f, 1.0f) * sinf(0.1f * elapsedTime)));

		// Moving the light over time
		m_PointLightPosition.x = 6.0f * sinf(elapsedTime);
		m_PointLightPosition.z = 6.0f * cosf(elapsedTime);

		// Attaching uniforms
		m_Shader->Attach();
		m_Shader->SetFloat3("u_AmbiantLight", m_AmbiantLightColor);
		m_Shader->SetFloat3("u_PointLightPosition", m_PointLightPosition);
		m_Shader->SetFloat3("u_PointLight", m_PointLightColor);
		m_Shader->SetFloat3("u_CameraPosition", m_CameraController.GetCamera().GetPosition());

		// Draw calls
		Entropy::Renderer::Draw(m_Shader, m_Plane.GetVertexArray(), m_PlaneTransform, m_CameraController.GetCamera());
		Entropy::Renderer::Draw(m_Shader, m_Nanosuit.GetVertexArray(), m_NanosuitTransform, m_CameraController.GetCamera());
		Entropy::Renderer::Draw(m_Shader, m_Cube.GetVertexArray(), glm::translate(glm::mat4(1.0f), m_PointLightPosition) * m_CubeTransform, m_CameraController.GetCamera());
	}

	virtual void OnApplicationEvent(Entropy::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Entropy::Shader* m_Shader;

#ifdef NT_PLATFORM_WINDOWS
	Entropy::Mesh m_Plane = Entropy::Mesh("assets/models/plane.obj");
	Entropy::Mesh m_Nanosuit = Entropy::Mesh("assets/models/nanosuit.obj");
	Entropy::Mesh m_Cube = Entropy::Mesh("assets/models/cube.obj");
#else
    Entropy::Mesh m_Plane = Entropy::Mesh("../assets/models/plane.obj");
    Entropy::Mesh m_Nanosuit = Entropy::Mesh("../assets/models/nanosuit.obj");
    Entropy::Mesh m_Cube = Entropy::Mesh("../assets/models/cube.obj");
#endif

	// Model transforms
	float scale = 100.0f;
	glm::mat4 m_PlaneTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f) * scale);
	glm::mat4 m_NanosuitTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
	glm::mat4 m_CubeTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));

	// Lights
	glm::vec3 m_AmbiantLightColor = glm::vec3(0.01f, 0.01f, 0.01f);
	glm::vec3 m_PointLightPosition = glm::vec3(-2.0f, 2.0f, 3.0f);
	float m_PointLightPower = 3.0f;
	glm::vec3 m_PointLightColor = glm::vec3(1.0f, 1.0f, 1.0f) * m_PointLightPower;

	// Camera controller
	Entropy::CameraController m_CameraController;
};

Entropy::Application* Entropy::CreateApplication()
{
	return new Game(1024, 720, "Entropy Engine Demo");
}

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

#ifdef NT_PLATFORM_WINDOWS
		m_Model.LoadOBJFromFile("assets/models/BrandenburgGate.obj");
		m_Plane.LoadOBJFromFile("assets/models/plane.obj");
		m_Cube.LoadOBJFromFile("assets/models/cube.obj");
#else
		m_Model.LoadOBJFromFile("../assets/models/BrandenburgGate.obj");
		m_Plane.LoadOBJFromFile("../assets/models/plane.obj");
		m_Cube.LoadOBJFromFile("../assets/models/cube.obj");
#endif

		m_Model.SetReflectivity(10.0f);
		m_Model.SetShineDamper(128.0f);
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
		Entropy::RenderCommand::Clear();

		// Moving the light over time
		m_PointLightPosition.x = 3.0f * sinf(elapsedTime);
		m_PointLightPosition.z = 3.0f * cosf(elapsedTime);

		// Attaching uniforms
		m_Shader->Attach();
		m_Shader->SetFloat3("u_CameraPosition", m_CameraController.GetCamera().GetPosition());

		m_Shader->SetFloat3("u_Light.position", m_PointLightPosition);
		m_Shader->SetFloat3("u_Light.color", m_PointLightColor);
		// Light will cover a distance of 50 meters
		m_Shader->SetFloat("u_Light.constant", 1.0f);
		m_Shader->SetFloat("u_Light.linear", 0.09f);
		m_Shader->SetFloat("u_Light.quadratic", 0.032f);

		Entropy::Renderer::Draw(m_Shader, m_Model, m_Identity, m_CameraController.GetCamera());
		Entropy::Renderer::Draw(m_Shader, m_Plane, m_PlaneTransform, m_CameraController.GetCamera());
		Entropy::Renderer::Draw(m_Shader, m_Cube, glm::translate(glm::mat4(1.0f), m_PointLightPosition) * m_CubeTransform, m_CameraController.GetCamera());
	}

	virtual void OnApplicationEvent(Entropy::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
#ifdef NT_PLATFORM_WINDOWS
	Entropy::Shader* m_Shader = Entropy::Shader::Create("assets/shaders/default.glsl");
	Entropy::Mesh m_Plane = Entropy::Mesh();
	Entropy::Mesh m_Cube = Entropy::Mesh();
	Entropy::Mesh m_Model = Entropy::Mesh();
#else
	Entropy::Shader* m_Shader = Entropy::Shader::Create("../assets/shaders/default.glsl");
	Entropy::Mesh m_Plane = Entropy::Mesh();
	Entropy::Mesh m_Cube = Entropy::Mesh();
	Entropy::Mesh m_Model = Entropy::Mesh();
#endif

	// Model transforms
	float scale = 100.0f;
	glm::mat4 m_PlaneTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f) * scale);
	glm::mat4 m_CubeTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
	glm::mat4 m_ModelTransform = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));

	glm::mat4 m_Identity = glm::mat4(1.0f);

	// Lights
	glm::vec3 m_PointLightPosition = glm::vec3(-2.0f, 2.0f, 3.0f);
	float m_PointLightPower = 0.8f;
	glm::vec3 m_PointLightColor = glm::vec3(1.0f, 1.0f, 1.0f) * m_PointLightPower;

	// Camera controller
	Entropy::CameraController m_CameraController;
};

Entropy::Application* Entropy::CreateApplication()
{
	return new Game(1024, 720, "Entropy Engine Demo");
}

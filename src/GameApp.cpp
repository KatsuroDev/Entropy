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
		//m_Plane.LoadOBJFromFile("assets/models/Plane.obj");
		m_Cube.LoadOBJFromFile("assets/models/Cube.obj");
		m_Bunny.LoadOBJFromFile("assets/models/Bunny.obj");
#else
		m_Model.LoadOBJFromFile("../assets/models/BrandenburgGate.obj");
		//m_Plane.LoadOBJFromFile("../assets/models/Plane.obj");
		m_Cube.LoadOBJFromFile("../assets/models/Cube.obj");
		m_Bunny.LoadOBJFromFile("../assets/models/Bunny.obj");
#endif

		// Generate plane terrain from perlin noise
		// size representing grid size in a direction
		m_Plane.GenerateTerrain(10, 0);


		//m_Model.SetReflectivity(300.0f);
		//m_Model.SetShineDamper(256.0f);

		m_Bunny.SetReflectivity(200.0f);
		m_Bunny.SetShineDamper(128.0f);

		// Setting title to Render API used
		Application::GetWindow().SetTitle(Application::GetWindow().GetTitle() + " - " + Entropy::RenderingAPI::GetName());
		Entropy::RenderCommand::SetClearColor(Entropy::EncodeSRGB(glm::vec4(0.3f, 0.5f, 0.8f, 1.0f)));
	}

	~Game()
	{
		delete m_Shader;
		delete m_Unlit;
	}

	virtual void OnUpdate(float elapsedTime) override
	{
		m_CameraController.OnUpdate(elapsedTime);

		// Gamma correction encoding
		//Entropy::RenderCommand::SetClearColor(Entropy::EncodeSRGB(glm::vec4(0.0862f, 0.3764f, 0.6549f, 1.0f) * sinf(0.1f * elapsedTime)));
		Entropy::RenderCommand::Clear();

		// Current time of simulation
		static float continousTime = 0.0f;
		continousTime += elapsedTime;

		// Moving the light over time
		m_PointLightPosition.x = 2.0f * sinf(continousTime * 1.0f);
		m_PointLightPosition.z = 2.0f * cosf(continousTime * 1.0f);

		// Attaching uniforms
		m_Shader->Attach();
		m_Shader->SetFloat3("u_Light.position", m_PointLightPosition);
		m_Shader->SetFloat3("u_Light.color", m_PointLightColor);
		// Light will cover a distance of 50 meters
		m_Shader->SetFloat("u_Light.constant", 1.0f);
		m_Shader->SetFloat("u_Light.linear", 0.09f);
		m_Shader->SetFloat("u_Light.quadratic", 0.032f);

		m_PlaneTransform = glm::rotate(m_PlaneTransform, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		Entropy::Renderer::Draw(m_Shader, m_Model, m_ModelTransform, m_CameraController.GetCamera());
		Entropy::Renderer::Draw(m_Shader, m_Plane, m_PlaneTransform, m_CameraController.GetCamera());
		Entropy::Renderer::Draw(m_Shader, m_Cube, glm::translate(glm::mat4(1.0f), m_PointLightPosition) * m_CubeTransform, m_CameraController.GetCamera());
		Entropy::Renderer::Draw(m_Shader, m_Bunny, m_Identity, m_CameraController.GetCamera());
	}

	virtual void OnApplicationEvent(Entropy::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
#ifdef NT_PLATFORM_WINDOWS
	Entropy::Shader* m_Shader = Entropy::Shader::Create("assets/shaders/default.glsl");
	Entropy::Shader* m_Unlit = Entropy::Shader::Create("assets/shaders/unlitPosGradient.glsl");

	Entropy::Mesh m_Plane = Entropy::Mesh();
	Entropy::Mesh m_Cube = Entropy::Mesh();
	Entropy::Mesh m_Model = Entropy::Mesh();
	Entropy::Mesh m_Bunny = Entropy::Mesh();
#else
	Entropy::Shader* m_Shader = Entropy::Shader::Create("../assets/shaders/default.glsl");
	Entropy::Shader* m_Unlit = Entropy::Shader::Create("../assets/shaders/unlitPosGradient.glsl");

	Entropy::Mesh m_Plane = Entropy::Mesh();
	Entropy::Mesh m_Cube = Entropy::Mesh();
	Entropy::Mesh m_Model = Entropy::Mesh();
	Entropy::Mesh m_Bunny = Entropy::Mesh();
#endif

	// Model transforms
	float scale = 1.0f;
	glm::mat4 m_PlaneTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f) * scale);
	glm::mat4 m_CubeTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
	glm::mat4 m_ModelTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 m_Identity = glm::mat4(1.0f);

	// Lights
	glm::vec3 m_PointLightPosition = glm::vec3(0.0f, 2.0f, 0.0f);
	float m_PointLightPower = 1.0f;
	glm::vec3 m_PointLightColor = glm::vec3(1.0f, 0.9f, 0.8f) * m_PointLightPower;

	// Camera controller
	Entropy::CameraController m_CameraController;
};

Entropy::Application* Entropy::CreateApplication()
{
	return new Game(1024, 720, "Entropy Engine Demo");
}

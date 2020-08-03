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
		: Application(width, height, title) {}

	virtual void OnCreate() override
	{
		m_CameraController.GetCamera().SetPosition(glm::vec3(0.0f, 1.0f, 1.0f));

		m_Model.LoadOBJFromFile("../assets/models/nanosuit.obj");
		m_Bunny.LoadOBJFromFile("../assets/models/bunny.obj");
		m_Sphere.LoadOBJFromFile("../assets/models/sphere.obj");

		// size representing grid size in a direction
		m_Plane.GenerateTerrain(100, 0);

		// static uniforms
		m_Shader->Attach();
		m_Shader->SetInt("u_Material.diffuse", 0);
		m_Shader->SetInt("u_Material.specular", 1);
		m_Shader->SetInt("u_Material.normalMap", 2);

		float power = 10.0f;
		m_Shader->SetFloat3("u_Light.ambient", glm::vec3(0.01f, 0.01f, 0.01f) * power);
		m_Shader->SetFloat3("u_Light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f) * power);
		m_Shader->SetFloat3("u_Light.specular", glm::vec3(1.0f, 1.0f, 1.0f) * power);
		// Light will cover a distance of 50 meters
		m_Shader->SetFloat("u_Light.constant", 1.0f);
		m_Shader->SetFloat("u_Light.linear", 0.09f);
		m_Shader->SetFloat("u_Light.quadratic", 0.032f);

		m_Shader->SetFloat("u_Material.shininess", 512.0f);
	}

	virtual void OnUpdate(float elapsedTime) override
	{
		m_CameraController.OnUpdate(elapsedTime);

		// Current time of simulation
		static float continousTime = 0.0f;
		continousTime += elapsedTime;

		// Moving the light over time
		m_PointLightPosition.x = 2.0f * sinf(continousTime);
		m_PointLightPosition.z = 2.0f * cosf(continousTime);

		// dynamic uniforms
		m_Shader->SetFloat3("u_Light.position", m_PointLightPosition);

		m_PlaneTransform = glm::rotate(m_PlaneTransform, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		diffuseMap->Attach(0);
		specularMap->Attach(1);
		Renderer::DrawInstanced(m_Shader, m_Model.GetVertexArray(), m_ModelTransform, m_CameraController.GetCamera(), 1000);
		diffuseMap->Attach(0);
		specularMap->Attach(1);
		normalMap->Attach(2);
		Renderer::Draw(m_Shader, m_Plane.GetVertexArray(), m_PlaneTransform, m_CameraController.GetCamera());
		diffuseMap->Attach(0);
		specularMap->Attach(1);
		Renderer::Draw(m_Shader, m_Bunny.GetVertexArray(), m_Identity, m_CameraController.GetCamera());
		//diffuseMap->Attach(0);
		//specularMap->Attach(1);
		//Renderer::Draw(m_Shader, m_Sphere.GetVertexArray(), m_SphereTransform, m_CameraController.GetCamera());
		diffuseMap->Attach(0);
		specularMap->Attach(1);
		Renderer::Draw(m_Shader, m_Sphere.GetVertexArray(), glm::translate(glm::mat4(1.0f), m_PointLightPosition) * m_SphereTransform, m_CameraController.GetCamera());
	}

	virtual void OnApplicationEvent(Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Ref<Texture2D> diffuseMap = Texture2D::Create("../assets/textures/container.png");
	Ref<Texture2D> specularMap = Texture2D::Create("../assets/textures/container_specular.png");
	Ref<Texture2D> normalMap = Texture2D::Create("../assets/textures/normal_map.png");

	Ref<Shader> m_Shader = Shader::Create("../assets/shaders/default.glsl");

	Mesh m_Plane = Mesh();
	Mesh m_Model = Mesh();
	Mesh m_Bunny = Mesh();
	Mesh m_Sphere = Mesh();

	// Model transforms
	glm::mat4 m_PlaneTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 m_SphereTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.01f, 0.01f, 0.01f));
	glm::mat4 m_ModelTransform = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 m_Identity = glm::mat4(1.0f);

	// Lights
	glm::vec3 m_PointLightPosition = glm::vec3(0.0f, 1.0f, 0.0f);

	// Camera controller
	CameraController m_CameraController = CameraController();
};

Entropy::Application* Entropy::CreateApplication()
{
	return new Game(1280, 720, "Entropy Engine Demo");
}

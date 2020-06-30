#pragma once

#include <GL/glm/glm.hpp>
#include <GL/glm/gtc/matrix_transform.hpp>

namespace Entropy {

	class Camera
	{
	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = -90.0f, float pitch = 0.0f, float fov = 45.0f, float speed = 2.5f, float sensitivity = 8.0f);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		// Getters
		inline glm::vec3 GetPosition() { return m_Position; }
		inline glm::vec3 GetFrontVec() { return m_Front; }
		inline glm::vec3 GetUpVec() { return m_Up; }
		inline glm::vec3 GetRightVec() { return m_Right; }
		inline glm::vec3 GetWorldUpVec() { return m_WorldUp; }
		inline float GetYaw() { return m_Yaw; }
		inline float GetPitch() { return m_Pitch; }
		inline float GetMovementSpeed() { return m_MovementSpeed; }
		inline float GetMouseSensitivity() { return m_MouseSensitivity; }
		inline float GetFov() { return m_Fov; }

		// Set attributes
		inline void SetPosition(float x, float y, float z) { m_Position = glm::vec3(x, y, z); }
		inline void SetPosition(glm::vec3 pos) { m_Position = pos; }
		inline void SetFrontVec(float x, float y, float z) { m_Front = glm::normalize(glm::vec3(x, y, z)); UpdateCameraVectors(); }
		inline void SetFrontVec(glm::vec3 front) { m_Front = glm::normalize(front); UpdateCameraVectors(); }
		inline void SetYaw(float yaw) { m_Yaw = yaw; UpdateCameraVectors(); }
		inline void SetPitch(float pitch) { m_Pitch = pitch; UpdateCameraVectors(); }
		inline void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }
		inline void SetMouseSensitivity(float sensitivity) { m_MouseSensitivity = sensitivity; }
		inline void SetFov(float fov) { m_Fov = fov; }


		// Mainly called on window resize
		void RecalculateViewProjectionMatrix();

	private:
		void UpdateCameraVectors();

	private:
		// Attributes
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;

		// Matrices
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		float m_Yaw;
		float m_Pitch;
		float m_Fov;
		float m_MovementSpeed;
		float m_MouseSensitivity;
	};
}

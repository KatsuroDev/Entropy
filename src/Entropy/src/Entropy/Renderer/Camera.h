#pragma once

#include <GL/glm/glm.hpp>
#include <GL/glm/gtc/matrix_transform.hpp>

namespace Entropy {

	class Camera
	{
	public:
		Camera(glm::vec3 position = glm::vec3(), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = -90.0f, float pitch = 0.0f, float fov = 45.0f);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void LookAt(const glm::vec3& orientation);

		// Getters
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetVelocity() const { return m_Velocity; }
		const glm::vec3& GetFrontVec() const { return m_Front; }
		const glm::vec3& GetUpVec() const { return m_Up; }
		const glm::vec3& GetRightVec() const { return m_Right; }
		const glm::vec3& GetWorldUpVec() const { return m_WorldUp; }

		const float GetYaw() const { return m_Yaw; }
		float GetPitch() const { return m_Pitch; }
		float GetMovementSpeed() const { return m_MovementSpeed; }
		float GetMouseSensitivity() const { return m_MouseSensitivity; }
		float GetMouseScrollSensitivity() const { return m_MouseScrollSensitivity; }
		float GetFov() const { return m_Fov; }

		// Setters
		void SetPosition(float x, float y, float z)
		{
			m_Position = glm::vec3(x, y, z);
			RecalculateLookAtMatrix();
			RecalculateViewProjectionMatrix();
		}

		void SetPosition(const glm::vec3& pos)
		{
			m_Position = pos; 
			RecalculateLookAtMatrix();
			RecalculateViewProjectionMatrix();
		}

		void SetVelocity(const glm::vec3& vel)
		{
			m_Velocity = vel;
		}

		void SetFrontVec(float x, float y, float z)
		{
			m_Front = glm::normalize(glm::vec3(x, y, z));
			UpdateCameraVectors();
		}

		void SetFrontVec(const glm::vec3& front)
		{
			m_Front = glm::normalize(front);
			UpdateCameraVectors();
		}

		void SetYaw(float yaw)
		{
			m_Yaw = yaw;
			UpdateCameraVectors();
		}

		void SetPitch(float pitch)
		{
			m_Pitch = pitch;
			UpdateCameraVectors();
		}

		void SetMovementSpeed(float speed)
		{
			m_MovementSpeed = speed;
		}

		void SetMouseSensitivity(float sensitivity)
		{
			m_MouseSensitivity = sensitivity;
		}

		void SetMouseScrollSensitivity(float scrollSensitivity)
		{
			m_MouseScrollSensitivity = scrollSensitivity;
		}

		void SetFov(float fov)
		{
			m_Fov = fov;
			RecalculateViewProjectionMatrix();
		}

		void ProcessMouseScroll(float value);
		void ProcessWindowResize();

		void RecalculateViewProjectionMatrix();
		void RecalculateLookAtMatrix();
		void UpdateCameraVectors();
		
	private:
		// Attributes
		glm::vec3 m_Velocity;
		glm::vec3 m_Position;
		glm::vec3 m_WorldUp;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;

		// Matrices
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		float m_Yaw;
		float m_Pitch;
		float m_Fov;
		float m_MovementSpeed = 10.0f;
		float m_MouseSensitivity = 0.2f;
		float m_MouseScrollSensitivity = 8.0f;
	};
}

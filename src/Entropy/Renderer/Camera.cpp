#include "Camera.h"

#include "../../Entropy/Core/Application.h"

#include "../../Entropy/Core/Logger.h"

#include <chrono>

namespace Entropy {

	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov)
		: m_Velocity(glm::vec3(0.0f, 0.0f, 0.0f)), m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_Fov(fov)
	{
		UpdateCameraVectors();

		RecalculateLookAtMatrix();
		RecalculateViewProjectionMatrix();
	}

	void Camera::LookAt(const glm::vec3& orientation)
	{
		m_Front = glm::normalize(orientation);

		// Also re-calucalte the right and up vector;
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));

		RecalculateLookAtMatrix();
		RecalculateViewProjectionMatrix();
	}

	void Camera::UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = cosf(glm::radians(m_Yaw)) * cosf(glm::radians(m_Pitch));
		front.y = sinf(glm::radians(m_Pitch));
		front.z = sinf(glm::radians(m_Yaw)) * cosf(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		// Also re-calucalte the right and up vector;
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void Camera::RecalculateViewProjectionMatrix()
	{
		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), aspectRatio, 0.1f, 1000.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::RecalculateLookAtMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::ProcessMouseScroll(float value)
	{
		float resultingFov = GetFov() - value * m_MouseScrollSensitivity;

		if (resultingFov >= 0.001 && resultingFov <= 120)
		{
			SetFov(resultingFov);
			RecalculateViewProjectionMatrix();
		}
	}

	void Camera::ProcessWindowResize()
	{
		RecalculateViewProjectionMatrix();
	}
}

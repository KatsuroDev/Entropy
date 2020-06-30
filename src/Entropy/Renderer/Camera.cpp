#include "Camera.h"

#include "../../Entropy/Core/Application.h"

#include "../../Entropy/Core/Logger.h"

namespace Entropy {

	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov, float speed, float sensitivity)
		: m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch), m_Fov(fov), m_MovementSpeed(speed), m_MouseSensitivity(sensitivity)
	{
		UpdateCameraVectors();

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
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
}

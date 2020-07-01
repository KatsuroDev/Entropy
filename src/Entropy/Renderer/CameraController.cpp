#include "CameraController.h"

#include "../../Entropy/Core/Logger.h"

#include "../../Entropy/Core/Input.h"
#include "../../Entropy/Core/KeyCodes.h"

namespace Entropy {

	CameraController::CameraController()
		: m_Camera(Camera())
	{
	}

	void CameraController::OnUpdate(float elapsedTime)
	{
		// Getting the time between this and the last frame
		static float lastTime = 0.0f;
		float frameTime = elapsedTime - lastTime;

		const float frictionCoeff = 4.0f;

		// View
		m_Camera.SetYaw(Input::GetMouseX() * m_Camera.GetMouseSensitivity());
		m_Camera.SetPitch(-Input::GetMouseY() * m_Camera.GetMouseSensitivity());

		// Clamping pitch
		if (m_Camera.GetPitch() > 89.0f)
			m_Camera.SetPitch(89.0f);
		if (m_Camera.GetPitch() < -89.0f)
			m_Camera.SetPitch(-89.0f);

		// Movement
		static float defaultMovementSpeed = m_Camera.GetMovementSpeed();

		// Boost key
		if (Input::IsKeyPressed(KeyCode::LeftControl))
		{
			m_Camera.SetMovementSpeed(50.0f);
		}
		else
		{
			m_Camera.SetMovementSpeed(defaultMovementSpeed);
		}

		if (Input::IsKeyPressed(KeyCode::W))
		{
			m_Camera.SetVelocity(m_Camera.GetVelocity() + m_Camera.GetFrontVec() * frameTime * m_Camera.GetMovementSpeed());
		}

		if (Input::IsKeyPressed(KeyCode::A))
		{
			m_Camera.SetVelocity(m_Camera.GetVelocity() - m_Camera.GetRightVec() * frameTime * m_Camera.GetMovementSpeed());
		}

		if (Input::IsKeyPressed(KeyCode::S))
		{
			m_Camera.SetVelocity(m_Camera.GetVelocity() - m_Camera.GetFrontVec() * frameTime * m_Camera.GetMovementSpeed());
		}

		if (Input::IsKeyPressed(KeyCode::D))
		{
			m_Camera.SetVelocity(m_Camera.GetVelocity() + m_Camera.GetRightVec() * frameTime * m_Camera.GetMovementSpeed());
		}

		if (Input::IsKeyPressed(KeyCode::Space))
		{
			m_Camera.SetVelocity(m_Camera.GetVelocity() + m_Camera.GetUpVec() * frameTime * m_Camera.GetMovementSpeed());
		}

		if (Input::IsKeyPressed(KeyCode::LeftShift))
		{
			m_Camera.SetVelocity(m_Camera.GetVelocity() - m_Camera.GetUpVec() * frameTime * m_Camera.GetMovementSpeed());
		}

		if (Input::IsKeyPressed(KeyCode::Delete))
		{
			m_Camera.SetVelocity(glm::vec3());
			m_Camera.SetPosition(glm::vec3());
		}

		// Calculating friction loss
		m_Camera.SetVelocity(m_Camera.GetVelocity() - m_Camera.GetVelocity() * frameTime * frictionCoeff);

		// Setting new position
		m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetVelocity() * frameTime);
		lastTime = elapsedTime;
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(ATTACH_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ATTACH_EVENT_FN(CameraController::OnWindowResized));
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_Camera.ProcessMouseScroll(e.GetYOffset());
		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_Camera.ProcessWindowResize();
		return false;
	}
}

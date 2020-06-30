#include "CameraController.h"

#include "../../Entropy/Core/Logger.h"

#include "../../Entropy/Core/Input.h"
#include "../../Entropy/Core/KeyCodes.h"

#include "../../Entropy/Core/Math/Constants.h"

namespace Entropy {

	CameraController::CameraController(float width, float height)
		: m_Width(width), m_Height(height), m_Camera(Camera())
	{
	}

	void CameraController::OnUpdate(float elapsedTime)
	{
		// TODO: Handle mouse input

	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(ATTACH_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(ATTACH_EVENT_FN(CameraController::OnWindowResized));
	}

	void CameraController::OnResize(float width, float height)
	{
		m_Width = width; m_Height = height;
		m_Camera.RecalculateViewProjectionMatrix();
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		float resultingFov = m_Camera.GetFov() - e.GetYOffset() * m_Camera.GetMouseSensitivity();

		if (resultingFov <= 120 && resultingFov >= 20)
		{
			m_Camera.SetFov(resultingFov);
			m_Camera.RecalculateViewProjectionMatrix();
		}

		return false;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}

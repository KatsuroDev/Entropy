#pragma once

#include "Camera.h"

#include "../../Entropy/Events/ApplicationEvent.h"
#include "../../Entropy/Events/MouseEvent.h"
#include "../../Entropy/Events/KeyEvent.h"

namespace Entropy {

	class CameraController
	{
	public:
		CameraController();

		void OnEvent(Event& e);
		void OnUpdate(float elapsedTime);

		Camera& GetCamera() { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		Camera m_Camera;
	};
}

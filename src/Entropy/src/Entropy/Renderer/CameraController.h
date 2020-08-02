#pragma once

#include "../Core/Core.h"

#include "Camera.h"

#include "../Events/ApplicationEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"

namespace Entropy {

	class CameraController
	{
	public:
		CameraController() {};

		void OnEvent(Event& e);
		void OnUpdate(float elapsedTime);

		Camera& GetCamera() { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		Camera m_Camera = Camera();
	};
}

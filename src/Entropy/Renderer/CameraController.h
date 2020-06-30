#pragma once

#include "Camera.h"

#include "../../Entropy/Events/MouseEvent.h"
#include "../../Entropy/Events/ApplicationEvent.h"

namespace Entropy {

	class CameraController
	{
	public:
		CameraController(float width, float height);

		void OnEvent(Event& e);
		void OnUpdate(float elapsedTime);

		void OnResize(float width, float height);

		const Camera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		Camera m_Camera;

		float m_Width;
		float m_Height;
	};
}

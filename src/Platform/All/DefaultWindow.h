#pragma once

#include "../../Entropy/Core/Window.h"
#include "../../Entropy/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Entropy {

	// The graphics context is part of the window
	class DefaultWindow : public Window
	{
	public:
		DefaultWindow(unsigned int width, unsigned int height, const char* title);
		virtual ~DefaultWindow();

		virtual unsigned int GetWidth() const override { return m_Data.Width; }
		virtual unsigned int GetHeight() const override { return m_Data.Height; }

		virtual void OnUpdate() override;

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(unsigned int width, unsigned int height, const char* title);
		virtual void Shutdown();

		struct WindowData
		{
			std::string Title = "";
			unsigned int Width = 0, Height = 0;
			bool VSync = true;

			EventCallbackFn EventCallback;
		};

		GraphicsContext* m_Context;
		GLFWwindow* m_Window;
		WindowData m_Data;
	};
}

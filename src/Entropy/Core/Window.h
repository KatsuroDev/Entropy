#pragma once

#include "Event.h"

namespace Entropy {

    struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Entropy Engine",
			        unsigned int width = 1280,
			        unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        void GetDimensions(int& width, int& height);

        void SetDimensions(int width, int height);

        void SetTitle(const char* title);

        bool ShouldClose();

        void SwapBuffers();

        void PollEvents();


        // New code implementation

        using EventCallbackFn = std::function<void(Event&)>;

        struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

        void OnUpdate();

        unsigned int GetWidth() const;
		unsigned int GetHeight() const;

        void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled);
        bool IsVSync() const;

        void* GetNativeWindow() const;

        WindowData m_Data;
    };
}

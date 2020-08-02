#pragma once

#include "../Core/Core.h"
#include "../Core/Input.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

#include <functional>

namespace Entropy {

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {};

        virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

        virtual void OnUpdate() = 0;

        virtual const std::string& GetTitle() = 0;
        virtual void SetTitle(const char* title) = 0;
        virtual void SetTitle(const std::string& title) = 0;

        virtual void SetCursorDisabled() = 0;
        virtual void SetCursorNormal() = 0;
        virtual bool GetCursorDisabled() const = 0;
        virtual bool GetCursorNormal() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(unsigned int width, unsigned int height, const char* title);
    };
}

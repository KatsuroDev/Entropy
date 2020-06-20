#pragma once

#include "../Events/Event.h"
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

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window* Create(unsigned int width, unsigned int height, const char* title);
    };
}

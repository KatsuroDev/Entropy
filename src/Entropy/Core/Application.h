#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Logger.h"

int main();

namespace Entropy {

    // Application class containing data
    class Application
    {
    public:
        Application(int width, int height, const char* title);
        // Will be inherited
        virtual ~Application();
        // Returns window reference
        Window& GetWindow() { return *m_Window; }

        void Stop();

    private:
        void Run();

        // Friend function are part of the class
        friend int ::main();

        // Support for only one window per application at the moment
        Window* m_Window;
        bool m_Running = true;
    };

    // To implement in CLIENT
    Application* CreateApplication();
}

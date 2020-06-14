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
        // Virtual because will be inherited
        virtual ~Application();
        // Returns generic window reference
        inline Window& GetWindow() { return *m_Window; }

        // Getter for the application's instance (use of polymorphism)
        Application& Get() { return *this; }

        // Public stopping
        void Terminate();

    private:
        void Run();

        // Friend function are part of the class
        friend int ::main();

        // Support for only one window per application at the moment
        Window* m_Window;

        // Flag for the application state, defaults to true
        bool m_Running = true;
    };

    // To implement in CLIENT
    Application* CreateApplication();
}

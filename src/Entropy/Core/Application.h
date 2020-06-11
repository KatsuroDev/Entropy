#pragma once

#include "Window.h"

int main();

namespace Entropy {

    // Application class containing data
    class Application
    {
    public:
        Application(int width, int height, const char* title);

        // Virtual because will be inherited
        virtual ~Application();

        inline Window& GetWindow() { return *m_Window; }

        // Getter for the application's instance (use of polymorphism)
        static Application& Get() { return *s_Instance; }

        // Public stopping
        void Terminate();

    private:
        // Private only starting
        void Run();

        static Application* s_Instance;

        // Friend function are PART of the class
        // They can have acces to private and protected data
        friend int ::main();

        // Support for only one window per application at the moment
        Window* m_Window;

        // Flag for the application state, defaults to true
        bool m_Running = true;
    };

    // To implement in CLIENT
    Application* CreateApplication();
}

#pragma once

#include "Window.h"

int main();

namespace Entro {

    // Application class containing data
    class Application
    {
    public:
        Application();
        
        // Virtual because will be inherited
        virtual ~Application();
        
        
        
        // Getter for the application's instance (use of polymorphism)
        static Application& Get() { return *s_Instance; }
        
    private:
        void Run();
        
        static Application* s_Instance;
        
        // Friend function are PART of the class
        // They can have acces to private and protected data
        friend int ::main();
        
        // Support for only one window per application at the moment
        // TODO: Multi window support
        Window* m_Window;
    };

    // To implement in CLIENT
    Application* CreateApplication();
}

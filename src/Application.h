#pragma once

#include "Window.h"

int main();

class Application
{
public:
    Application();
    virtual ~Application();

    void Run();

    static Application& Get() { return *s_Instance; }

private:
        Window* m_Window;

		static Application* s_Instance;
		friend int main();
};

// Implemented in client
Application* CreateApplication();

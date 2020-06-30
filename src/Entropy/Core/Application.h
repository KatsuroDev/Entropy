#pragma once

#include "Window.h"
#include "../Events/Event.h"
#include "../Events/ApplicationEvent.h"

int main();

namespace Entropy {

    // Application class containing data
    class Application
    {
    public:
        Application(int width, int height, const char* title);
        virtual ~Application();

        void OnEvent(Event& e);
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnApplicationEvent(Event& e) = 0;

        Window& GetWindow() { return *m_Window; }

        static Application& Get() { return *s_Instance; };

        void Stop();

    private:
        void Run();

        bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

        // Friend function are part of the class
        friend int ::main();

        static Application* s_Instance;
        Window* m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();
}

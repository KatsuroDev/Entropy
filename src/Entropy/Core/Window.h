#pragma once

// We only use glfw for window creation
// If we needed to use windows APIs to create a window,
// we would not include platform specefic headers here
// Rather create a new class inheriting this Window class
// and making the entire class abstract
#include <GLFW/glfw3.h>

namespace Entropy {

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

    private:
        // Contains the GLFWwindow ptr
        // Would not have this if window was more generic
        GLFWwindow* m_Window;
    };
}

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Entro {

    // inline functions are wrappers for the actual glfw function calls

    // Provides a usefull callback for resizing the framebuffer
    // Re-drawing the buffer is done by default on resize
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        inline void GetDimensions(int& width, int& height) { glfwGetWindowSize(m_Window, &width, &height); }

        inline void SetDimensions(int width, int height) { glfwSetWindowSize(m_Window, width, height); }

        inline void SetTitle(const char* title) { glfwSetWindowTitle(m_Window, title); }

        inline bool ShouldClose() { return glfwWindowShouldClose(m_Window); }

        inline void SwapBuffers() { glfwSwapBuffers(m_Window); }

        inline void PollEvents() { glfwPollEvents(); }

    private:
        // Contains the GLFWwindow ptr
        GLFWwindow* m_Window;
    };
}

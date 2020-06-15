#include "Window.h"

#include "Logger.h"
#include "Renderer.h"

// We only use glfw for window creation
// If we needed to use windows APIs to create a window,
// we would not include platform specefic headers here
// Rather create a new class inheriting this Window class
// and making the entire class abstract

#include <GLFW/glfw3.h>

static GLFWwindow* s_Window;

namespace Entropy {

    // Provides a usefull callback for resizing the framebuffer
    // Re-drawing the buffer is done by default on resize
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        Renderer::Clear();
        Renderer::SetViewport(0, 0, width, height);
        // Re-render the scene because the current frame was drawn for the old resolution
        glfwSwapBuffers(window);
    }

    Window::Window(int width, int height, const char* title)
    {
        /* Initialize the library */
        if (!glfwInit())
            glfwTerminate();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        /* Create a windowed mode window and its OpenGL context */
        s_Window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!s_Window)
            glfwTerminate();

        /* Make the window's context current */
        glfwMakeContextCurrent(s_Window);

        /* Linking the call back function for stretching */
        glfwSetFramebufferSizeCallback(s_Window, framebuffer_size_callback);

        /* V-sync */
        glfwSwapInterval(1);
    }

    void Window::GetDimensions(int& width, int& height)
    {
        glfwGetWindowSize(s_Window, &width, &height);
    }

    void Window::SetDimensions(int width, int height)
    {
        glfwSetWindowSize(s_Window, width, height);
    }

    void Window::SetTitle(const char* title)
    {
        glfwSetWindowTitle(s_Window, title);
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(s_Window);
    }

    void Window::SwapBuffers()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(s_Window);
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    Window::~Window()
    {
        glfwTerminate();
    }


    // New code...
    void* Window::GetNativeWindow() const
    {
        return s_Window;
    }
}

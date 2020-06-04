#include "Window.h"

namespace Entro {

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
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
        m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!m_Window)
            glfwTerminate();

        /* Make the window's context current */
        glfwMakeContextCurrent(m_Window);

        /* Linking the call back function for stretching */
        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

        /* V-sync */
        glfwSwapInterval(1);


        /* Init glew */
        if(glewInit() != GLEW_OK)
            glfwTerminate();
    }

    Window::~Window()
    {
        glfwTerminate();
    }
}

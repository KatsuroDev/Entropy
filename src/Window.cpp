#include "Window.h"

Window::Window(int width, int height, const char* title)
    : m_Width(width), m_Height(height), m_Title(title)
{
    /* Init GLFW */
    if (!glfwInit())
    {
        glfwTerminate();
        //std::cout << "An error occured while attempting to Init GLFW";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Only to use on MACOS
#endif

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        //std::cout << "An error occured while attempting to create the window";
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);

    /* Giving the window his framebufferSizeCallback function */
    glfwSetFramebufferSizeCallback(m_Window, framebufferSizeCallback);


    /* Init glew */
    if(glewInit() != GLEW_OK)
    {
        glfwTerminate();
        //std::cout << "An error occured while attempting to Init GLEW";
    }
}

Window::~Window()
{
    /* flush glfw */
    glfwTerminate();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_Window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

int Window::GetWidth()
{
    glfwGetWindowSize(m_Window, &m_Width, &m_Height);
    return m_Width;
}

int Window::GetHeight()
{
    glfwGetWindowSize(m_Window, &m_Width, &m_Height);
    return m_Height;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    inline void GetDimentions(int& width, int& height) { glfwGetWindowSize(m_Window, &width, &height); }

    inline void SetDimentions(int width, int height) { glfwSetWindowSize(m_Window, width, height); }

    inline bool ShouldClose() { return glfwWindowShouldClose(m_Window); }

    inline void SwapBuffers() { glfwSwapBuffers(m_Window); }

    inline void PollEvents() { glfwPollEvents(); }

private:
    GLFWwindow* m_Window;
};

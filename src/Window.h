#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

class Window
{
public:
    Window(int width = 800, int height = 600, const char* title = "");
    ~Window();

    // GETTERS AND SETTERS
    int GetWidth();
    int GetHeight();

    /* returns the closing state of the window */
    bool ShouldClose();

    /* swaps the screen buffers */
    void SwapBuffers();

    /* polls events */
    void PollEvents();


private:
    GLFWwindow* m_Window;
    int m_Width;
    int m_Height;
    const char* m_Title;
};

#endif

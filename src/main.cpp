#include <iostream>

#include "Window.h"

int main()
{
    Window window(600, 480, "Entropy Engine");
    std::cout << "Welcome to Entropy!\n";

    /* Loop until the user closes the window */
    while (!window.ShouldClose())
    {
        /* Render here */
        glClearColor(0.0f, 0.39f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int width, height;
        window.GetDimentions(width, height);
        std::cout << width << ", " << height << "\n";

        /* Swap front and back buffers */
        window.SwapBuffers();

        /* Poll for and process events */
        window.PollEvents();
    }
}

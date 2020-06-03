#include <iostream>
#include "Window.h"

// Entry point is controlled by the engine NOT the client
// So the engine calls the game, not the opposite
int main()
{
    /* allocate on the heap! We wan't to explicitly control the lifetime of this object */
    Window window = Window(800, 600, "Entropy Engine");
    std::cout <<"Welcome to Entropy Engine!";

    /* Loop until the user closes the window */
    while (!window.ShouldClose())
    {
        glClearColor(0.0f, 0.39f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        std::cout << window.GetWidth() << ", " << window.GetHeight() << std::endl;
        window.SwapBuffers();
        window.PollEvents();
    }

    return 0;
}

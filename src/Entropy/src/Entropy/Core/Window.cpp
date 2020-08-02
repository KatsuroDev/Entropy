#include "Window.h"

#include "Logger.h"
#include "../../Platform/All/DefaultWindow.h"

namespace Entropy {

    Scope<Window> Window::Create(unsigned int width, unsigned int height, const char* title)
    {
        // Platform specefic window creation is done here:
        // Returns a defuult window instance
        return CreateScope<DefaultWindow>(width, height, title);
        NT_INFO("Created a new window");
    }
}

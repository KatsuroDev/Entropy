// ENTRY POINT HERE
// -----------------------------------

#include "Application.h"

Entropy::Application* Entropy::CreateApplication();

int main()
{
    // Init log class
    Entropy::Logger::Trace("Hello from the logger! Warming transistors...");

    /* application creation */
    auto app = Entropy::CreateApplication();
    app->Run();
    delete app;
    Entropy::Logger::Trace("Hey! Come back next time.");

    return 0;
}

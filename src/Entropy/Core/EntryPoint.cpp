// ENTRY POINT HERE
// -----------------------------------

// This file contains the main() function
// The engine creates an application

#include "Application.h"

Entropy::Application* Entropy::CreateApplication();

int main()
{
    // Init log class
    Entropy::Logger::Trace("Hello from the logger! Warming transistors...\n");

    /* application creation */
    auto app = Entropy::CreateApplication();
    app->Run();
    delete app;
    Entropy::Logger::Trace("Hey! Come back next time.\n");

    return 0;
}

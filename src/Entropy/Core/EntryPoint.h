#pragma once

// Temp... TODO: implement logging
#include <iostream>

// ENTRY POINT HERE
// -----------------------------------

// This file contains the main() function
// The engine creates an application

#include "Application.h"

extern Entro::Application* Entro::CreateApplication();

int main()
{
    // Init log class
    std::cout << "Hello from the logger! Warming transistors...\n";

    /* application creation */
    auto app = Entro::CreateApplication();
    app->Run();
    delete app;
    std::cout << "Hey! Come back next time.\n";

    return 0;
}

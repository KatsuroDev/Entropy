#pragma once

// ENTRY POINT HERE
// -----------------------------------

// This file contains the main() function
// The engine creates an application

#include "Application.h"

extern Application* CreateApplication();

int main()
{
    // Init log class

    /* application creation */
    auto app = CreateApplication();

    app->Run();

    // Destruction of the application
    delete app;

    return 0;
}

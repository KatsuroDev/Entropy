// ENTRY POINT HERE
// -----------------------------------
#pragma once
// This file contains the main() function
// The engine creates an application

extern Application* CreateApplication();

int main()
{
    // Init log class

    /* application creation */
    Application* app = CreateApplication();

    app->Run();

    // Destruction of the application
    delete app;

    return 0;
}

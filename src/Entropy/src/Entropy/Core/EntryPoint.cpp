// ENTRY POINT HERE
// -----------------------------------

#include "Application.h"

#if defined(_DEBUG)
#include <iostream>
#endif

Entropy::Application* Entropy::CreateApplication();

int main()
{
	/* application creation */
	auto app = Entropy::CreateApplication();
	app->Run();
	delete app;

#if defined(NT_PLATFORM_WINDOWS) && defined(_DEBUG)
	std::cin.get();
#endif

	return 0;
}

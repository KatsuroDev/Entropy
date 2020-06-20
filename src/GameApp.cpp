// This is our game using Entropy Engine
// To be seperated into a seperated new project
// 1. #include "Entropy.h"
// 2. Create a game class that inherits from Entropy::Application
// 3. Call Entropy::CreateApplication(width, height, title) that returns an Entropy::Application*
// You're set!

#include "Entropy.h"

class Game : public Entropy::Application
{
public:
    Game(int width, int height, const char* title)
        : Application(width, height, title)
    {
        // Temp
        //Entropy::Renderer::AttachData();
    }

    ~Game()
    {

    }
};

Entropy::Application* Entropy::CreateApplication()
{
    return new Game(1024, 720, "Entropy Engine Demo");
}

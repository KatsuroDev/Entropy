// This is our game using Entropy Engine

#include "Entropy.h"

class Game : public Entropy::Application
{
public:
    Game(int width, int height, const char* title)
        : Application(width, height, title)
    {

    }

    ~Game()
    {

    }
};

Entropy::Application* Entropy::CreateApplication()
{
    return new Game(720, 480, "Entropy Engine Demo");
}

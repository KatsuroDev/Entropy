#include "../Entropy.h"

class Game : public Entro::Application
{
public:
    Game()
    {

    }

    ~Game()
    {

    }
};

Entro::Application* Entro::CreateApplication()
{
    return new Game();
}

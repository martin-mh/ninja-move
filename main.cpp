#include "game.h"

int main()
{
    Game game;

    if(game.init())
        game.start();
    else
        return 0;

    return 0;
}

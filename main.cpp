#include "SnakeGame.h"

int main()
{
    SnakeGame* game = new SnakeGame();
    game->run();

    free(game);

    return EXIT_SUCCESS;
}

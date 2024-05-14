#ifndef __GAME__
#define __GAME__
#include <SDL.h>
#define RUNNING_STATE 3
#define STOPPPED_STATE 4
#include "Board.h"
#include "graphics.h"
struct Game{
    Board board;
    int game_state;
    Graphics graphics;
    Game();
    void restart();
    void update(SDL_Event *event);
    bool check_endGame();
};
#endif // __GAME__

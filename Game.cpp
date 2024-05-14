#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(){
    restart();
}
void Game::update(SDL_Event *event){
        if (event->type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            int cols = (x - X_BOARD) / CELL_SIZE;
            int rows = (y - Y_BOARD) / CELL_SIZE;
            if (x >= X_BOARD && y >= Y_BOARD && board.isFieldEmpty(rows, cols)){
                board.move(rows, cols);
                if (board.next_move == X_CELL){
                    graphics.renderTexture(graphics.cell_x, 685, 140);
                }
                else {
                    graphics.renderTexture(graphics.cell_o, 685,140);
                }
                Mix_PlayChannel(-1, graphics.gChunk[0], 0);
            }
        }

}
void Game::restart(){
    board.board_reset();
    game_state = RUNNING_STATE;
}
bool Game::check_endGame(){
    if (board.gameOver()){
        game_state = STOPPPED_STATE;
        return true;
    }
    return false;

}

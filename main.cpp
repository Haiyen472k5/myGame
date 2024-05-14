#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "graphics.h"
#include "defs.h"
#include "Board.h"
#include "Game.h"
#include "App.h"

using namespace std;

int main(int argc, char *argv[]){
    Game tictactoe;
    App app;
    tictactoe.graphics.initGame();
    bool quit = false;
    SDL_Event event;
    SDL_Event app_event;
    while (!quit){
        SDL_PollEvent(&app_event);
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (app.app_state == MENU_STATE){
            tictactoe.graphics.play_(tictactoe.graphics.gMusic);
            if (x >= 308 && y>= 315 && x <= 485 && y<=375){
                tictactoe.graphics.renderMenu_exit();
                if(app_event.type == SDL_MOUSEBUTTONDOWN)
                    Mix_PlayChannel(-1, tictactoe.graphics.gChunk[1], 0);
            }
            else if (x >= 267 && y>= 224 && x <=536 && y <= 280){
                tictactoe.graphics.renderMenu_start();
                if(app_event.type == SDL_MOUSEBUTTONDOWN)
                    Mix_PlayChannel(-1, tictactoe.graphics.gChunk[1], 0);
            }
            else{
                tictactoe.graphics.renderMenu();
            }
            app.update(&app_event);
        }
        else if (app.app_state == PLAYING_STATE){
            bool _quit = false;
            int count_x = 0;
            int count_o = 0;
            tictactoe.graphics.setFrame(count_x, count_o);
            while (!_quit){
                SDL_PollEvent(&event);
                switch (tictactoe.game_state){
                    case RUNNING_STATE:
                        tictactoe.update(&event);
                        if (event.type == SDL_MOUSEBUTTONDOWN){
                            int i, j;
                            SDL_GetMouseState(&i, &j);
                            if (i>= 618 && j>= 542 && i <= 780 && j <= 554){
                                _quit = true;
                                Mix_PlayChannel(-1, tictactoe.graphics.gChunk[1], 0);
                                app.app_state = MENU_STATE;
                                tictactoe.restart();
                            }
                            else if (i >= 628 && j >= 435 && i <= 768 && j<=453){
                                Mix_PlayChannel(-1, tictactoe.graphics.gChunk[1], 0);
                                tictactoe.graphics.setFrame(count_x, count_o);
                                tictactoe.restart();
                            }
                        }
                        tictactoe.graphics.render(tictactoe.board);
                        if (tictactoe.check_endGame()){
                            Mix_PauseMusic();
                            Mix_PlayChannel(-1, tictactoe.graphics.endGame, 0);
                            if (tictactoe.board.board_state == X_WON){
                                tictactoe.graphics.render_X_WON();
                                ++count_x;
                            }
                            else if (tictactoe.board.board_state == O_WON){
                                tictactoe.graphics.render_O_WON();
                                ++count_o;
                            }
                            else{
                                tictactoe.graphics.render_DRAW();
                            }
                        }
                        tictactoe.graphics.presentScene();
                        break;
                    case STOPPPED_STATE:
                        if (event.type == SDL_MOUSEBUTTONDOWN){
                            int i, j;
                            SDL_GetMouseState(&i, &j);
                            if (i >= 628 && j >= 435 && i <= 768 && j<= 453){
                                Mix_PlayChannel(-1, tictactoe.graphics.gChunk[1], 0);
                                tictactoe.graphics.setFrame(count_x, count_o);
                                tictactoe.restart();
                                tictactoe.graphics.play_(tictactoe.graphics.gMusic);
                            }
                            else if (i>= 618 && j>= 542 && i <= 780 && j <= 554){
                                Mix_PlayChannel(-1, tictactoe.graphics.gChunk[1], 0);
                                _quit = true;
                                app.app_state = MENU_STATE;
                                tictactoe.restart();
                            }
                        }
                        break;
                }
            }
        }
        else{
            quit = true;
        }
    }
    cerr << "End game";
    return 0;
}

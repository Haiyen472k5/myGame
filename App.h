#ifndef __APP__
#define __APP__
#include <SDL.h>
#define MENU_STATE 5
#define PLAYING_STATE 6
#define QUIT_STATE 7


struct App{
    int app_state;
    App(){
        app_state = MENU_STATE;
    }
    void update(SDL_Event *event){
        if (event->type == SDL_QUIT){
            app_state = QUIT_STATE;
        }
        if (event->type == SDL_MOUSEBUTTONDOWN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= 308 && y>= 315 && x <= 485 && y<=375){

                app_state = QUIT_STATE;
            }
            else if (x >= 267 && y>= 224 && x <=536 && y <= 280){
                app_state = PLAYING_STATE;
            }

        }
    }


};
#endif // __APP__

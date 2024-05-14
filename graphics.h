#ifndef _GRAPHICS__H
#define _GRAPHICS__H
#include <string>
#include <iostream>
#include <cstring>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "defs.h"
#include "Board.h"

struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Texture *background, *cell_empty, *cell_o, *cell_x, *side_ground, *side_2_ground, *restart, *back_to_menu;
    Mix_Music *gMusic;///nhac nen
    Mix_Chunk *gChunk[2];///tieng tick
    TTF_Font* gFont[3];
    Mix_Chunk* endGame;

	Graphics();
	~Graphics();

	void logErrorAndExit(const char* msg, const char* error);
	void init();
	void prepareScene(SDL_Texture * background);
    void presentScene();
    SDL_Texture *loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
    void initGame();
    void render(Board &board);
    Mix_Music *loadMusic(const char* path);
    void play_(Mix_Music *gMusic);
    Mix_Chunk* loadSound(const char* path);
    void play(Mix_Chunk *gChunk);
    void setbkGround_game(){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }
    TTF_Font *loadFont(const char* path,int size);
    SDL_Texture *renderText(const char* text, TTF_Font* font, SDL_Color text_color);
    void render_X_WON();
    void render_O_WON();
    void render_DRAW();
    void renderMenu();
    void setFrame(int n, int m);
    void renderMenu_start();
    void renderMenu_exit();
    void render_x_(int n);
    void render_o_(int n);

};

#endif // _GRAPHICS__H

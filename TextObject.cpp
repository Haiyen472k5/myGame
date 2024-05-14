#include "TextObject.h"

TextObject::TextObject(){
    ;
}
TextObject::~TextObject(){
    ;
}

void TextObject::setColor(const int& type){
    if (type == 0){
        SDL_Color _Color = {255, 0, 0, 255};
        Color = _Color;
    }
    if (type == 1){
        SDL_Color _Color = {255, 255, 0, 255};
        Color = _Color;
    }
}

void TextObject::createGameText(TTF_Font* font, int x, int y){
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, Color);
    if( textSurface == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.renderer, textSurface);
    if( texture == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }
    SDL_FreeSurface( textSurface );
    graphics.renderTexture(texture, x, y);
    graphics.presentScene();
}

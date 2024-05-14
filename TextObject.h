#ifndef __TEXT_OBJECT__
#define __TEXT_OBJECT__
#include "graphics.h"
#include "SDL_ttf.h"

class TextObject{
public:
    enum TexColor{
        RED_TEXT = 0,
        YELLOW_TEXT = 1,
    };

    TextObject();
    ~TextObject();
    Graphics graphics;

    void setText(const char* _text){
        text = _text;
    }
    void setColor(const int& type);
    void createGameText(TTF_Font* font, int x, int y);
    Graphics graphic;


private:
    const char* text;
    SDL_Color Color;

};
#endif // __TEXT_OBJECT__

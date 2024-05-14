#include "graphics.h"

Graphics::Graphics(){
    renderer = nullptr;
    window = nullptr;
    background = nullptr;
    cell_empty = nullptr;
    cell_o = nullptr;
    cell_x = nullptr;
    gChunk[0] = nullptr;
    gChunk[1] = nullptr;
    endGame = nullptr;
    gMusic = nullptr;
    gFont[0] = nullptr;
    gFont[1] = nullptr;
    gFont[2] = nullptr;
    side_ground = nullptr;
    side_2_ground = nullptr;
    restart = nullptr;
    back_to_menu = nullptr;
}

Graphics::~Graphics(){
    SDL_DestroyTexture(cell_empty);
    SDL_DestroyTexture(cell_o);
    SDL_DestroyTexture(cell_x);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(side_ground);
    SDL_DestroyTexture(side_2_ground);
    SDL_DestroyTexture(restart);
    SDL_DestroyTexture(back_to_menu);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(gChunk[0]);
    Mix_FreeChunk(gChunk[1]);
    Mix_FreeMusic(gMusic);
    cell_empty = nullptr;
    cell_o = nullptr;
    cell_x = nullptr;
    background = nullptr;
    side_ground = nullptr;
    IMG_Quit();
    gChunk[0] = nullptr;
    gMusic = nullptr;
    gChunk[1] = nullptr;
    Mix_Quit();
    TTF_CloseFont(gFont[0]);
    TTF_CloseFont(gFont[1]);
    TTF_CloseFont(gFont[2]);
    gFont[0] = nullptr;
    gFont[1] = nullptr;
    gFont[2] = nullptr;
    TTF_Quit();
    renderer = nullptr;
    window = nullptr;
    SDL_Quit();

}

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        logErrorAndExit("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    if (TTF_Init() == -1){
        logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
    }
}

void Graphics::prepareScene(SDL_Texture * background)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
}

void Graphics::presentScene()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char *filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(renderer, texture, src, &dest);
}
void Graphics::initGame(){
    init();
    background = loadTexture("image//menu.png");
    cell_empty = loadTexture("image//cell_empty.png");
    cell_o = loadTexture("image//cell_o.png");
    cell_x = loadTexture("image//cell_x.png");
    side_ground = loadTexture("image//frame.png");
    side_2_ground = loadTexture("image//frame2.png");
    restart = loadTexture("image//restart.png");
    back_to_menu = loadTexture("image//back.png");
    gMusic = loadMusic("Sound//game.mp3");
    gChunk[0] = loadSound("Sound//click.wav");
    gChunk[1] = loadSound("Sound//menu.wav");
    endGame = loadSound("Sound//endGame.wav");
    gFont[0] = loadFont("Font//RebellionSquad-ZpprZ.ttf",54);
    gFont[1] = loadFont("Font//Purisa-BoldOblique.ttf",36);
    gFont[2] = loadFont("Font//Play.ttf", 80);
}

void Graphics::render(Board &board){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            int x = X_BOARD + j*CELL_SIZE;
            int y = Y_BOARD + i*CELL_SIZE;
            switch(board.BOARD_PIECE[i][j]){
                case EMPTY_CELL: renderTexture(cell_empty, x, y); break;
                case X_CELL: renderTexture(cell_x, x, y); break;
                case O_CELL: renderTexture(cell_o, x, y); break;
            }
        }
    }
    presentScene();
}

Mix_Music* Graphics::loadMusic(const char* path){
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                        "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}

void Graphics::play_(Mix_Music *gMusic){
    if (gMusic == nullptr) return;
    if (Mix_PlayingMusic() == 0){
        Mix_PlayMusic(gMusic, -1);
    }
    else if (Mix_PausedMusic() == 1){
        Mix_ResumeMusic();
    }
}

Mix_Chunk* Graphics::loadSound(const char* path){
    Mix_Chunk *gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                        "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    }
    return gChunk;
}

TTF_Font* Graphics::loadFont(const char* path, int size)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", path);
    TTF_Font *gFont = TTF_OpenFont(path, size);
    if (gFont == nullptr){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
    return gFont;
}

SDL_Texture* Graphics::renderText(const char* text, TTF_Font* font, SDL_Color textColor)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
    if( textSurface == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if( texture == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }

    SDL_FreeSurface( textSurface );
    return texture;
}

void Graphics::play(Mix_Chunk *gChunk){
    if (gChunk != nullptr){
        Mix_PlayChannel(-1, gChunk, 0);
    }
}

void Graphics::render_X_WON(){
    SDL_Color Color = {255, 165, 0, 255};
    SDL_Texture* _X_ = renderText("X WON!",gFont[0], Color);
    renderTexture(_X_, 605,225);
    presentScene();
}

void Graphics::render_O_WON(){
    SDL_Color Color = {255, 0, 0, 255};
    SDL_Texture* _O_ = renderText("O WON!", gFont[0], Color);
    renderTexture(_O_, 605,225);
    presentScene();
}

void Graphics::render_DRAW(){
    SDL_Color Color = {0, 255, 255, 255};
    SDL_Texture* _DRAW_ = renderText("DRAW", gFont[0], Color);
    renderTexture(_DRAW_, 605,225);
    presentScene();
}

void Graphics::setFrame(int n, int m){
    setbkGround_game();
    renderTexture(side_ground, 600,0);
    renderTexture(side_2_ground, 600,100);
    renderTexture(restart,600,400);
    renderTexture(back_to_menu, 600, 500);
    SDL_Color Color = {0, 0, 0, 255};
    SDL_Texture* turn = renderText("Turn", gFont[1], Color);
    renderTexture(turn, 645, 90);
    renderTexture(cell_x, 685, 140);
    render_x_(n);
    render_o_(m);

}

void  Graphics::renderMenu_start(){
    prepareScene(background);
    SDL_Color Color = {0, 0, 0, 255};
    SDL_Color _Color = {255, 0, 0 ,255};
    SDL_Texture* play = renderText("Start", gFont[2],_Color);
    SDL_Texture* exit = renderText("Exit", gFont[2], Color);
    renderTexture(play, 265, 205);
    renderTexture(exit, 305, 301);
    presentScene();


}


void Graphics::renderMenu_exit(){
    prepareScene(background);
    SDL_Color Color = {0, 0, 0, 255};
    SDL_Color _Color = {255, 0, 0 ,255};
    SDL_Texture* play = renderText("Start", gFont[2],Color);
    SDL_Texture* exit = renderText("Exit", gFont[2], _Color);
    renderTexture(play, 265, 205);
    renderTexture(exit, 305, 301);
    presentScene();
}

void Graphics::renderMenu(){
    prepareScene(background);
    SDL_Color Color = {0, 0, 0, 255};
    SDL_Texture* play = renderText("Start", gFont[2],Color);
    SDL_Texture* exit = renderText("Exit", gFont[2], Color);
    renderTexture(play, 265, 205);
    renderTexture(exit, 305, 301);
    presentScene();
}

void Graphics::render_x_(int n){
    std::string val = std::to_string(n);
    SDL_Color Color = {0,0,0,255};
    std::string res = "X Win: " + val;
    char* x_ = new char [res.length()+1];
    strcpy(x_, res.c_str());
    SDL_Texture *x_win = renderText(x_, gFont[1], Color);
    renderTexture(x_win, 600,300);

}

void Graphics::render_o_(int n){
    std::string val = std::to_string(n);
    SDL_Color Color = {0,0,0,255};
    std::string res = "O Win: " + val;
    char* o_ = new char [res.length()+1];
    strcpy(o_, res.c_str());
    SDL_Texture *o_win = renderText(o_, gFont[1], Color);
    renderTexture(o_win, 600,350);

}





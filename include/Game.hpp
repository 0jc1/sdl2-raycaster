#include <SDL.h>
#include <iostream>
#include <string>
#include "Player.hpp"



class Game
{

public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void stop();

    double fov;
    int screenWidth;
    int screenHeight;

    Player *p;

    bool running() { return isRunning; };

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

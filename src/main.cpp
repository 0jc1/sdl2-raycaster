#include <iostream>
#include <chrono>
#include "Game.hpp"

using namespace std;

/*
    main.cpp
*/

const int WIDTH = 640 * 2, HEIGHT = 480 * 2;
const long FPS_LIMIT = 60;

Game *game = nullptr;

int main(int argc, char *argv[])
{
    double a = 0;
    double b = 0;
    long delta = 0;
    double fps = 0;

    game = new Game();

    game->init("SDL2 Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

    // main game loop
    while (game->running())
    {
        a = SDL_GetTicks();
        delta = a - b;

        if (delta > 1000 / FPS_LIMIT)
        {
            fps = 1000 / delta;
            b = a;

            game->handleEvents();

            game->update();
            game->render();

        }
    }

    game->stop();

    return EXIT_SUCCESS;
}
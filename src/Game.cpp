#include "Game.hpp"
#include <cmath>
#include <vector>
#include <thread>
#include <atomic>
#include <iostream>

#define mapWidth 24
#define mapHeight 24

// TODO map files
int worldMap[mapWidth][mapHeight] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

Game::Game() {}

// destructor
Game::~Game()
{
    this->stop();
}

void Game::stop()
{
    std::cout << "stopping" << std::endl;
    this->clean();
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("Compiled SDL version = %d.%d.%d\n", compiled.major, compiled.minor,
           compiled.patch);
    printf("Linked SDL version   = %d.%d.%d\n", linked.major, linked.minor,
           linked.patch);

    int flags = SDL_WINDOW_ALLOW_HIGHDPI;

    if (fullscreen)
    {
        flags = flags | SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems initialized" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        screenWidth = width;
        screenHeight = height;

        if (window)
        {
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

        if (renderer)
        {
            std::cout << "Renderered created" << std::endl;
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        std::atexit(SDL_Quit);

        //direction vector should be perpendicular to camera plane vector
        p = new Player(22.0, 11.5, -1, 0);

        isRunning = true;
    }
    else
    {
        std::string sdlErr = std::to_string(*SDL_GetError());

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init()", SDL_GetError(), 0);
        SDL_Log("SDL_Init(): %s", SDL_GetError());

        std::cout << "Could not initialize SDL: " + sdlErr << std::endl;
        isRunning = false;
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
        }
    }

    if (keystates[SDL_SCANCODE_A])
    {
        // rotate player direction vector
        double oldDirX = p->dir.x;
        p->dir.x = p->dir.x * cos(p->rotSpeed) - p->dir.y * sin(p->rotSpeed);
        p->dir.y = oldDirX * sin(p->rotSpeed) + p->dir.y * cos(p->rotSpeed);

        // rotate camera plane
        double oldPlaneX = p->plane.x;
        p->plane.x = p->plane.x * cos(p->rotSpeed) - p->plane.y * sin(p->rotSpeed);
        p->plane.y = oldPlaneX * sin(p->rotSpeed) + p->plane.y * cos(p->rotSpeed);
    }
    else if (keystates[SDL_SCANCODE_D])
    {
        // rotate player direction vector
        double oldDirX = p->dir.x;

        p->dir = Vector2(p->dir.x * cos(-p->rotSpeed) - p->dir.y * sin(-p->rotSpeed), oldDirX * sin(-p->rotSpeed) + p->dir.y * cos(-p->rotSpeed));

        // rotate camera plane
        double oldPlaneX = p->plane.x;

        p->plane = Vector2(p->plane.x * cos(-p->rotSpeed) - p->plane.y * sin(-p->rotSpeed), oldPlaneX * sin(-p->rotSpeed) + p->plane.y * cos(-p->rotSpeed));
    }

    if (keystates[SDL_SCANCODE_W])
    {
        //collision check
        if (worldMap[int(p->pos.x + p->dir.x * p->walkSpeed)][int(p->pos.y)] == 0)
            p->pos.x += p->dir.x * p->walkSpeed;
        if (worldMap[int(p->pos.x)][int(p->pos.y + p->dir.y * p->walkSpeed)] == 0)
            p->pos.y += p->dir.y * p->walkSpeed;
    }
    else if (keystates[SDL_SCANCODE_S])
    {
        if (worldMap[int(p->pos.x - p->dir.x * p->walkSpeed)][int(p->pos.y)] == 0)
            p->pos.x -= p->dir.x * p->walkSpeed;
        if (worldMap[int(p->pos.x)][int(p->pos.y - p->dir.y * p->walkSpeed)] == 0)
            p->pos.y -= p->dir.y * p->walkSpeed;
    }
}

void Game::update()
{

}

void Game::render()
{
    // background
    SDL_SetRenderDrawColor(renderer, 10, 0, 160, 255);
    SDL_RenderClear(renderer);

    int pitch = 80;

    double sideDistX;
    double sideDistY;

    int mapX;
    int mapY;

    int stepX;
    int stepY;

    int side;    // was a NS or a EW wall hit?

    int hit; 

    for (int x = 0; x < screenWidth; x++)
    {
        // calculate ray position and direction
        double cameraX = 2 * (x / (double)screenWidth) - 1; // x-coordinate in camera space
        double rayDirX = p->dir.x + p->plane.x * cameraX;
        double rayDirY = p->dir.y + p->plane.y * cameraX;

        // which box of the map we're in
        mapX = int(p->pos.x);
        mapY = int(p->pos.y);


        // length of ray from one x or y-side to next x or y-side
        double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
        double perpWallDist;

        hit = 0; // was there a wall hit?

        // calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (p->pos.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - p->pos.x) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (p->pos.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - p->pos.y) * deltaDistY;
        }


        // perform Digital Differential Analysis (DDA)
        while (hit == 0)
        {
            // jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
            if (worldMap[mapX][mapY] > 0) {
                hit = 1;
                break;
            }
        }

        // Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect)
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        // Calculate height of line to draw on screen
        int lineHeight = (int)(screenHeight / perpWallDist);

        // calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + screenHeight / 2 + pitch;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2 + pitch;
        if (drawEnd >= screenHeight)
            drawEnd = screenHeight - 1;

        // give x and y sides different brightness
        int divColor = 1;
        if (side == 1)
        {
            divColor = 2;
        }

        // choose wall color
        switch (worldMap[mapX][mapY])
        {
        case 1:
            SDL_SetRenderDrawColor(renderer, 255 / divColor, 0, 0, 255);
            break; // red
        case 2:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255 / divColor, 255);
            break; // green
        case 3:
            SDL_SetRenderDrawColor(renderer, 0, 255 / divColor, 0, 255);
            break; // blue
        case 4:
            SDL_SetRenderDrawColor(renderer, 255 / divColor, 255 / divColor, 255 / divColor, 255);
            break; // white
        default:
            SDL_SetRenderDrawColor(renderer, 150 / divColor, 150 / divColor, 0, 255);
            break; // yellow
        }

        // draw the pixels of the stripe as a vertical line
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }
    SDL_Quit();
    std::cout << "cleanup" << std::endl;
}
#pragma once
#include <SDL2/SDL.h>

class GameWindow
{
    public:
        static int height;
        static int width;
        static SDL_Renderer* renderer;
        static SDL_Window* window;
};
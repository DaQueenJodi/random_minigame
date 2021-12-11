#pragma once
#include <SDL2/SDL.h>
class Game
{
    private:
        static SDL_Event event;

        static bool running;
    public:
        static void HandleEvents();
        static void Update();
        static bool Running();
        static void Start();
        static void Clean();
        static void CreatePlayer(int x, int y, unsigned int speed, const char* path);

        static SDL_Window* window;
        static SDL_Renderer* renderer;
};


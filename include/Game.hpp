#pragma once
#include <SDL2/SDL.h>
class Game
{
    private:
        // for debug
        static float last_x;
        static float last_y;
        static float last_speed;

        static SDL_Event event;

        static bool running;
    public:
        static void HandleEvents();
        static void Update();
        static bool Running();
        static void Start();
        static void Clean();
        static void CreatePlayer(float x, float y, float s, const char* path);

        static void HandleDebug();

        static SDL_Window* window;
        static SDL_Renderer* renderer;
};


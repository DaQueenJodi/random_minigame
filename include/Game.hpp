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
        static void Draw();
        static bool Running();
        static void Start();
        static void Clean();
        static void CreatePlayer(float x, float y, float s, const char* path);
        static void CreateGun(unsigned int per_shot, unsigned int max_ammo, const char* path, const char* path2);
        
        static float get_degree(float orgin_x, float orgin_y, float other_x, float other_y);

        static void HandleDebug();

        static int Window_Width;
        static int Window_Height;

        static SDL_Window* window;
        static SDL_Renderer* renderer;
};


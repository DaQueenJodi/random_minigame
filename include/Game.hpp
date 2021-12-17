#pragma once
#include <SDL2/SDL.h>
#include "Enemies.hpp"
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

        template <class entity>
        static SDL_Rect entity_to_rect(const entity& src);


        static void HandleEvents();
        static void Update();
        static void Draw();
        static bool Running();
        static void Start();
        static void Clean();
        static void CreateEnemy(EnemyUtils::Enemies enemy_choice);
        static void CreatePlayer(float x, float y, float s, const char* path);
        static void CreateGun(unsigned int per_shot, unsigned int max_ammo, int dmg, const char* path, const char* path2);
        
        static float get_degree(float orgin_x, float orgin_y, float other_x, float other_y);

        static void HandleDebug();
};


#pragma once
#include <SDL2/SDL_image.h>
#include <vector>
class Enemy
{
    public:
        int health;
        SDL_Texture* image;
        static std::vector<Enemy*> enemies;
        int get_health();
};
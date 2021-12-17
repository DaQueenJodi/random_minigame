#pragma once
#warning c++_sucks
#include <SDL2/SDL_image.h>
#include <vector>
class Enemy
{
    public:
        int health;
        SDL_Texture* image;
        float xpos;
        float ypos;
        int height;
        int width;
        static std::vector<Enemy*> enemies;
};

class Basic_Shooter : public Enemy
{
    public:
        Basic_Shooter(int x, int y);
};
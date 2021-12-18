#pragma once
#include "Entity.hpp"
#include <SDL2/SDL_image.h>
#include <vector>
class Enemy : public Entity
{
    public:
        int health;
        SDL_Texture* image;
};

class Basic_Shooter : public Enemy
{
    public:
        Basic_Shooter(int x, int y);
        ~Basic_Shooter();
};
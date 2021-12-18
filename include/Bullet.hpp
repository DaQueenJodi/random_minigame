#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"

class Bullet
{
    private:
        float xpos;
        float ypos;
        float speed;
        float direction;
        float angle;
        int height;
        int width;
        unsigned int damage;
        SDL_Texture* image;
        friend class Game;
    public:
        void Move();
        Bullet(float x, float y, float real_angle, float bull_angle, int dmg, SDL_Texture* img);
        ~Bullet();
    
};
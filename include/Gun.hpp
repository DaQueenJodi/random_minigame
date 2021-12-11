#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL_image.h>
#include "Game.hpp"
#include "Bullet.hpp"

class Gun
{
    private:
        static SDL_Texture* image;
        static SDL_Texture* bullet_image;
        static float xpos;
        static float ypos;
        static int height;
        static int width;
        static float angle;
        static unsigned int max_ammo;
        static unsigned int ammo_per_shot;
        static std::string gun_name;
        friend class Game;
    public:
        static std::vector<Bullet*> bullets;
        static void PewPew();
        static SDL_Rect gun_rect;
};
#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL_image.h>
#include "Game.hpp"
#include "Bullet.hpp"

class Gun
{
    private:
        static Gun* curr_gun;
        SDL_Texture* image;
        SDL_Texture* bullet_image;
        int xpos;
        int ypos;
        int height;
        int width;
        float angle;
        static unsigned int max_ammo;
        static unsigned int ammo_per_shot;
        static std::string gun_name;
        static int bullet_damage;
        friend class Game;
    public:
        ~Gun();
        Gun();
        Gun(int x, int y);
        static std::vector<Bullet*> bullets;
        static void PewPew();
        static SDL_Rect gun_rect;
};
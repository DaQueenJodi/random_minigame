#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"


class Player
{
private:
    static int xpos;
    static int ypos;
    static int height;
    static int width;
    static unsigned int speed;
    static bool canshoot;
    static bool canwalk;
    static SDL_Texture* image;
    friend class Game;
public:
    static unsigned int get_speed(); 
    static void set_speed(unsigned int num);
    static SDL_Rect player_rect;
};

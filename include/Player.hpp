#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"


class Player
{
private:
    static float xpos;
    static float ypos;
    static int height;
    static int width;
    static float speed;
    static bool canshoot;
    static bool canwalk;
    static SDL_Texture* image;
    friend class Game;
    friend class Gun;
public:
    static void Up();
    static void Left();
    static void Down();
    static void Right();
    static float get_speed(); 
    static void set_speed(float num);
    static void CheckBounds();
};

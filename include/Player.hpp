#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"
#include "Entity.hpp"


class Player : public Entity
{
public:
    static float speed;
    SDL_Texture* image;

    static void Up();
    static void Left();
    static void Down();
    static void Right();
    static void CheckBounds();
    Player(int x, int y);
};

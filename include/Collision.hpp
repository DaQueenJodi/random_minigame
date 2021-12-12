#pragma once
#include <SDL2/SDL.h>
#include <vector>
class Collision
{
    public:
        static bool AABB(SDL_Rect rect1, SDL_Rect rect2);
        static int out_of_bounds(int x, int y);
};
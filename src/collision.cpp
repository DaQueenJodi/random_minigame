#include "Collision.hpp"
#include "Game.hpp"

bool Collision::AABB(SDL_Rect rect1, SDL_Rect rect2)
{
    // if rect1 is inside of rect2 (or vise versa), return true 
    if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x &&
        rect1.y < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y)
        {
            return true;
        }
        return false;
}

int Collision::out_of_bounds(int x, int y)
{
    if (x < 0  )
    {
        return 1;
    }
    if (x > Game::Window_Width)
    {
        return 2;
    }
    if (y < 0)
    {
        return 3;
    }
    if (y > Game::Window_Height)
    {
        return 4;
    }
    return 0;
}
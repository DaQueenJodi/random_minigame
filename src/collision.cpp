#include "Collision.hpp"
#include "GameWindow.hpp"

bool Collision::AABB(SDL_Rect a, SDL_Rect b)
{
    bool x_overlaps =  (a.x < b.x + b.w) && (a.x + a.w > b.x );
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_overlaps && y_overlaps);
}

int Collision::out_of_bounds(int x, int y)
{
    if (x < 0  )
    {
        return 1;
    }
    if (x > GameWindow::width )
    {
        return 2;
    }
    if (y < 0)
    {
        return 3;
    }
    if (y > GameWindow::height )
    {
        return 4;
    }
    return 0;
}
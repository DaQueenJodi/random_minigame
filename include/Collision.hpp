#include <SDL2/SDL.h>
#include <vector>
class Collision
{
    static void AABB(SDL_Rect rect1, SDL_Rect rect2)
    {
        // if rect1 is inside of rect2 (or vise versa), return true 
        if (rect1.x < rect2.x + rect2.width && rect1.x + rect1.width > rect2.x &&
            rect1.y < rect2.y + rect2.height && rect1.y + rect1.height > rect2.y)
    }

}
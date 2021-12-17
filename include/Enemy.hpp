#pragma once
#include <SDL2/SDL_image.h>
#include <vector>
class Enemy
{
    public:
        int health;
        SDL_Texture* image;
        float xpos;
        float ypos;
        int height;
        int width;
        friend class Game;
        
        static std::vector<Enemy*> enemies;
        int get_health();
};

class Basic_Shooter : public Enemy
{
    public:
        Basic_Shooter(int x, int y);
};
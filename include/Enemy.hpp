#pragma once
#include <SDL2/SDL_image.h>
#include <vector>
class Enemy
{
    private:
        int health;
        SDL_Texture* image;
        float xpos;
        float ypos;
        int height;
        int width;
        friend class Game;
    public:
    static std::vector<Enemy*> enemies;
        int get_health();
        Enemy(float x, float y, int health, const char* path);

};
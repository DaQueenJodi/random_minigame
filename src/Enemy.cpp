#include "Enemy.hpp"
#include "Game.hpp"

std::vector<Enemy*> Enemy::enemies;

Enemy::Enemy(float x, float y, int h, const char* path)
{
    xpos = x;
    ypos = y;
    health = h;
    image = IMG_LoadTexture(Game::renderer, path);
    SDL_QueryTexture(image, NULL, NULL, &width, &height);
}

int Enemy::get_health()
{
    return health;
}
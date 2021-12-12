#include "Enemy.hpp"
#include "Basic_Shooter.hpp"
#include "Game.hpp"

Basic_Shooter::Basic_Shooter()
{
    health = 10;
    image = IMG_LoadTexture(Game::renderer, "gfx/basic_shooter.png");
    Basic_Shooter::enemy_list.push_back(this);
}
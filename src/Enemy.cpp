#include "Enemy.hpp"
#include "GameWindow.hpp"

std::vector<Enemy*> Enemy::enemies = {};

Basic_Shooter::Basic_Shooter(int x, int y)
{
    xpos = x;
    ypos = y;
    image = IMG_LoadTexture(GameWindow::renderer, "gfx/basic_shooter.png");
    SDL_QueryTexture(image, NULL, NULL, &width, &height);

}
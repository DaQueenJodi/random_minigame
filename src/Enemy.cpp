#include "Enemy.hpp"
#include "GameWindow.hpp"

Basic_Shooter::Basic_Shooter(int x, int y)
{
    type = "Basic_Shooter";
    health = 10;
    xpos = x;
    ypos = y;
    image = IMG_LoadTexture(GameWindow::renderer, "gfx/basic_shooter.png");
    SDL_QueryTexture(image, NULL, NULL, &width, &height);
}

Basic_Shooter::~Basic_Shooter()
{
    SDL_DestroyTexture(image);
}
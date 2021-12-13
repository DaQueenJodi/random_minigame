#include "Bullet.hpp"
#include <math.h>


Bullet::Bullet(float x, float y, float real_angle, float bull_angle, int dmg, SDL_Texture* img)
{
    xpos = x;
    ypos = y;
    angle = real_angle;
    direction = bull_angle;
    image = img;
    speed = 10;
    damage = dmg;
    SDL_QueryTexture(image, NULL, NULL, &width, &height);
}

void Bullet::Move()
{
    xpos += speed * cos(angle);
    ypos += speed * sin(angle);
}
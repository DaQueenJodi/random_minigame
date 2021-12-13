#include "Player.hpp"
#include "Gun.hpp"
#include "Bullet.hpp"
#include <string>
std::vector<Bullet*> Gun::bullets;

void Gun::PewPew()
{
    int mouse_x, mouse_y;
    SDL_PumpEvents(); // make sure the mouse is updated.
    SDL_GetMouseState(&mouse_x, &mouse_y);

    Bullet* newBullet = new Bullet(Gun::xpos, Gun::ypos,std::atan2(mouse_y - Player::ypos, mouse_x - Player::xpos) , Gun::angle, Gun::bullet_damage, Gun::bullet_image);
    Gun::bullets.push_back(newBullet);

}
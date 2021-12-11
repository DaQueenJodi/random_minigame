#include "Player.hpp"

int Player::xpos = 0;
int Player::ypos = 0;
unsigned int Player::speed = 1;
SDL_Texture* Player::image = NULL;


void Player::set_speed(unsigned int num)
{
    Player::speed = num;
}
unsigned int Player::get_speed()
{
    return Player::speed;
}
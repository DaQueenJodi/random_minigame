#include "Player.hpp"

float Player::xpos;
float Player::ypos;
float Player::speed;
SDL_Texture* Player::image = NULL;


void Player::set_speed(float num)
{
    Player::speed = num;
}
float Player::get_speed()
{
    return Player::speed;
}
void Player::Up()
{
    Player::ypos -= 10 * Player::speed;
}
void Player::Left()
{
    Player::xpos -= 10 * Player::speed;
}
void Player::Down()
{
    Player::ypos += 10 * Player::speed;
}
void Player::Right()
{
    Player::xpos += 10 * Player::speed;
}
#include "Player.hpp"
#include "Collision.hpp"
#include "GameWindow.hpp"

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
    if (Player::canwalk)
        Player::ypos -= 10 * Player::speed;
}
void Player::Left()
{
    if (Player::canwalk)
        Player::xpos -= 10 * Player::speed;
}
void Player::Down()
{
    if (Player::canwalk)
        Player::ypos += 10 * Player::speed;
}
void Player::Right()
{
    if (Player::canwalk)
        Player::xpos += 10 * Player::speed;
}

void Player::CheckBounds()
{
    if (Player::xpos < 0)
    {
        Player::xpos = 0;
    }
    if (Player::xpos > GameWindow::width - 35 )
    {
        Player::xpos = GameWindow::width - 35;
    }
    if (Player::ypos <  0)
    {
        Player::ypos = 0;
    }
    if ( Player::ypos > GameWindow::height - 35)
    {
        Player::ypos = GameWindow::height - 35 ;
    }
}
#include "Player.hpp"
#include "Collision.hpp"

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

bool Player::CheckBounds()
{
    int result = Collision::out_of_bounds(Player::xpos, Player::ypos);
    if (result)
    {
        if (result == 1)
        {
            Player::xpos = 0;
        }
        else if (result == 2)
        {
            Player::xpos = Game::Window_Width;
        }
        else if (result == 3)
        {
            Player::ypos = 0;
        }
        else if (result == 4)
        {
            Player::ypos = Game::Window_Height;
        }
        return true;
    }
    return false;
}
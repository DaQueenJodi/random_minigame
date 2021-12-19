#include "Player.hpp"
#include "Collision.hpp"
#include "GameWindow.hpp"
#include "Entities.hpp"

float Player::speed;



void Player::Up()
{
        Entities::curr_player->ypos -= 10 * Player::speed;
}
void Player::Left()
{
       Entities::curr_player->xpos -= 10 * Player::speed;
}
void Player::Down()
{
        Entities::curr_player->ypos += 10 * Player::speed;
}
void Player::Right()
{
       Entities::curr_player->xpos += 10 * Player::speed;
}

void Player::CheckBounds()
{
    if (Entities::curr_player->xpos < 0)
    {
        Entities::curr_player->xpos = 0;
    }
    if (Entities::curr_player->xpos > GameWindow::width)
    {
        Entities::curr_player->xpos = GameWindow::width;
    }
    if (Entities::curr_player->ypos <  0)
    {
        Entities::curr_player->ypos = 0;
    }
    if ( Entities::curr_player->ypos > GameWindow::height)
    {
       Entities::curr_player->ypos = GameWindow::height;
    }
}


Player::Player(int x, int y)
{
    xpos = x;
    ypos = y;
    speed = 1;
}
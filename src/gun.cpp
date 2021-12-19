#include "Player.hpp"
#include "Gun.hpp"
#include "Bullet.hpp"
#include "GameWindow.hpp"
#include "Entities.hpp"
#include <string>

std::vector<Bullet*> Gun::bullets;

void Gun::PewPew()
{
    Gun* gun = Entities::curr_gun;
    Player* player = Entities::curr_player;

    int mouse_x, mouse_y;
    SDL_PumpEvents(); // make sure the mouse is updated.
    SDL_GetMouseState(&mouse_x, &mouse_y);

    Bullet* newBullet = new Bullet(gun->xpos, gun->ypos,std::atan2(mouse_y - player->ypos, mouse_x - player->xpos) , gun->angle, Gun::bullet_damage, gun->bullet_image);
    Gun::bullets.push_back(newBullet);

}

Gun::Gun()
{
    
}

Gun::~Gun()
{
    SDL_DestroyTexture(image);
    SDL_DestroyTexture(bullet_image);
}

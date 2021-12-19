#include "Debug.hpp"
#include "Player.hpp"

bool Debug::debug_enabled = false;
SDL_Texture* Debug::hitbox = IMG_LoadTexture(GameWindow::renderer, "gfx/hitbox_test.png");

void Debug::display_text()
{
    Player* player = Entities::curr_player;
    Gun* gun = Entities::curr_gun;

        printf("current X coordinate: %d \n", player->xpos);
       
        printf("current Y coordinate: %d \n", player->ypos);

        printf("current player speed: %f \n", player->speed);

        //printf("Player can shoot: %s \n", player->canshoot? "yes" : "no");

        //printf("Player can walk: %s \n", player->canwalk ? "yes" : "no");

        printf("Bullet Damage: %d \n", Gun::bullet_damage);

        printf("Bullets: %zx \n", Gun::bullets.size());
        
        for (unsigned int i = 0; i < Entities::enemies.size(); ++i)
        {
            auto& e = Entities::enemies[i];
            
            printf("Enemy #%u has %d hp left\n", i + 1, e->health);
        }
        //clear the screen 
        printf("\033[H\033[2J\033[3J");
}

void Debug::display_hitboxes()
{
     for (auto& e: Entities::enemies)
        {
                e->image = Debug::hitbox; 
        }

        for (auto& b: Gun::bullets)
        {
            b->image = Debug::hitbox;
        }
}
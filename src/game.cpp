#include "Keyboard.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Gun.hpp"
#include "Collision.hpp"
#include "EnemyUtils.hpp"
#include "Enemy.hpp"
#include  <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameWindow.hpp"
#include "Entities.hpp"

bool Game::running = false;
SDL_Event Game::event;

int Player::width;
int Player::height;
bool Player::canshoot;
bool Player::canwalk;


unsigned int Gun::max_ammo;
unsigned int Gun::ammo_per_shot;
int Gun::bullet_damage;



// debug stuff
float Game::last_speed;
float Game::last_y;
float Game::last_x;
SDL_Texture* Game::test_hitbox = IMG_LoadTexture(GameWindow::renderer, "gfx/hitbox_test.png");


int GameWindow::width;
int GameWindow::height;
SDL_Renderer* GameWindow::renderer;
SDL_Window* GameWindow::window;

std::vector<Enemy*> Entities::enemies;

Gun* Entities::curr_gun;


void Game::CreatePlayer(float x, float y, float s, const char* path)
{
    Player::canwalk = true;
    Player::canshoot = true;
    Player::speed = s;
    Player::xpos = x;
    Player::ypos = y;
    Player::image = IMG_LoadTexture(GameWindow::renderer, path); 
    // set the height and width of player based on the image height and width
    SDL_QueryTexture(Player::image, NULL, NULL, &Player::width, &Player::height);

}

void Game::CreateGun(unsigned int per_shot, unsigned int ammo_max, int dmg, const char* path, const char* path2)
{
    Gun* gun = new Gun;
    Gun::ammo_per_shot = per_shot;
    Gun::max_ammo = ammo_max;
    gun->image = IMG_LoadTexture(GameWindow::renderer, path);
    gun->bullet_image = IMG_LoadTexture(GameWindow::renderer, path2);
    Gun::bullet_damage = dmg;
    // set the height and width of the gun and bullet based on the image height and width
    SDL_QueryTexture(gun->image, NULL, NULL, &gun->width, &gun->height);
    Entities::curr_gun = gun;

}


bool Game::Running()
{
    return Game::running;
}


void Game::Start()
{   
    SDL_GetWindowSize(GameWindow::window, &GameWindow::width, &GameWindow::height); 
    Game::running = true;
}

void Game::HandleEvents()
{
    HandleKeyboard();
    while (SDL_PollEvent(&Game::event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Game::running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    Gun::PewPew(); 
            default:
                break;
        }
    }
}

float Game::get_degree(float orgin_x, float orgin_y, float other_x, float other_y)
{
    float delta_y = orgin_y - other_y;
    float delta_x = orgin_x - other_x;   
    return (atan2(delta_y, delta_x)*180.0000)/3.1416; // math stuff stolen from stack overflow: https://stackoverflow.com/questions/21174767/how-do-you-rotate-a-sprite-based-on-mouse-position
}

void Game::Update()
{
    // set mouse_x and mouse_y to the current coordiantes of the mouse
    int mouse_x, mouse_y;
    SDL_PumpEvents(); // make sure the mouse is updated.
    SDL_GetMouseState(&mouse_x, &mouse_y);
    {
    Gun* gun = Entities::curr_gun;
    gun->xpos = Player::xpos + 100;
    gun->ypos = Player::ypos;
    gun->angle = Game::get_degree(gun->xpos, gun->ypos, mouse_x, mouse_y);
    }

    for (unsigned int i = 0; i < Gun::bullets.size(); ++i)
    {
        auto* b = Gun::bullets[i];
        b->Move();

        if (Collision::out_of_bounds(b->xpos, b->ypos))
        {
            delete b;
            Gun::bullets.erase(Gun::bullets.begin()+i);
        }
    }
    
    for (unsigned int i = 0; i < Entities::enemies.size(); ++i)
    {
        auto* e = Entities::enemies[i];
        //e->Move;

        SDL_Rect enemy_rect = entity_to_rect(e);
        // offset the x value so that guns appears near the player; not on top
        enemy_rect.x += 100;

         for (auto& b : Gun::bullets)
         {

                SDL_Rect bullet_rect = entity_to_rect(b);

            if (Collision::AABB(bullet_rect, enemy_rect))
            {
                   e->health -= b->damage;
            }
         }

            if (e->health < 1)
            {
                delete e;
                Entities::enemies.erase(Entities::enemies.begin()+i);
            }

    }
            

}

void Game::Draw()
{

    Gun* gun = Entities::curr_gun;

    SDL_RenderClear(GameWindow::renderer);

    SDL_Rect player_rect;
    player_rect.x = gun->xpos;
    player_rect.y = gun->ypos;
    player_rect.h = gun->height;
    player_rect.w = gun->width;

   
    SDL_RenderCopy(GameWindow::renderer, Player::image, NULL, &player_rect);   

    SDL_Rect gun_rect;
    gun_rect.x = gun->xpos;
    gun_rect.y = gun->ypos;
    gun_rect.h = gun->height;
    gun_rect.w = gun->width;
    SDL_RenderCopyEx(GameWindow::renderer, gun->image, NULL, &gun_rect, gun->angle, NULL, SDL_FLIP_NONE);   

    for (auto& b : Gun::bullets)
    {
        SDL_Rect bull_rect;
        bull_rect.x = b->xpos;
        bull_rect.y = b->ypos;
        bull_rect.h = b->height;
        bull_rect.w = b->width;
        SDL_RenderCopyEx(GameWindow::renderer, b->image, NULL, &bull_rect, b->direction, NULL, SDL_FLIP_NONE);  
    }

    for (auto& e : Entities::enemies)
    {
        SDL_Rect enemy_rect;
        enemy_rect.x = e->xpos;
        enemy_rect.y = e->ypos;
        enemy_rect.h = e->height;
        enemy_rect.w = e->width;
        SDL_RenderCopy(GameWindow::renderer, e->image, NULL, &enemy_rect);  
    }

    SDL_RenderPresent(GameWindow::renderer);
    
}

void Game::Clean()
{
    for (auto& b : Gun::bullets)
    {
        delete b;
    }
    SDL_DestroyTexture(Player::image);
    SDL_DestroyRenderer(GameWindow::renderer);
    SDL_DestroyWindow(GameWindow::window);
    SDL_Quit();
}




void Game::CreateEnemy(EnemyUtils::EnemyType enemy_choice)
{
    Enemy* new_enemy = nullptr;
    switch (enemy_choice)
    {
        case EnemyUtils::EnemyType::Basic_Shooter:
            new_enemy = new Basic_Shooter(100,100);
    }

    Entities::enemies.push_back(new_enemy);
    
}
template <class entity>
SDL_Rect Game::entity_to_rect(const entity& src)
{
    SDL_Rect dst;

    dst.x = src->xpos;
    dst.y = src->ypos;
    dst.h = src->height;
    dst.w =src->width;
    
    return dst;
}




void Game::HandleDebug()
{

    //bunch of messy code but no one will use this but me so who cares 
        
        printf("current X coordinate: %f \n", Player::xpos);
       
        printf("current Y coordinate: %f \n", Player::ypos);

        printf("current player speed: %f \n", Player::speed);

        printf("Player can shoot: %s \n", Player::canshoot ? "yes" : "no");

        printf("Player can walk: %s \n", Player::canwalk ? "yes" : "no");

        printf("Bullet Damage: %d \n", Gun::bullet_damage);

        printf("Bullets: %lx \n", Gun::bullets.size());
        
        for (unsigned int i = 0; i < Entities::enemies.size(); ++i)
        {
            auto& e = Entities::enemies[i];
            
            printf("Enemy #%u has %d hp left\n", i + 1, e->health);
        }
      

        for (auto& e: Entities::enemies)
        {
                e->image = Game::test_hitbox; 
        }

        for (auto& b: Gun::bullets)
        {
            b->image = Game::test_hitbox;
        }

       //SDL_DestroyTexture(test_hitbox);

        // clear the screen 
        printf("\033[H\033[2J\033[3J");
    
}

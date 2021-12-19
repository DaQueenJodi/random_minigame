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
#include <iostream>

bool Game::running = false;
SDL_Event Game::event;


unsigned int Gun::max_ammo;
unsigned int Gun::ammo_per_shot;
int Gun::bullet_damage;



// debug stuff
SDL_Texture* Game::test_hitbox = IMG_LoadTexture(GameWindow::renderer, "gfx/hitbox_test.png");

SDL_Surface* cursor_surface = IMG_Load("gfx/cursor.png");
SDL_Cursor* cursor = SDL_CreateColorCursor(cursor_surface, 0, 0);

int GameWindow::width;
int GameWindow::height;
SDL_Renderer* GameWindow::renderer;
SDL_Window* GameWindow::window;

std::vector<Enemy*> Entities::enemies;

Gun* Entities::curr_gun;
Player* Entities::curr_player;


void Game::CreatePlayer(float x, float y, const char* path)
{   
    Player* player = new Player(x, y);
    player->image = IMG_LoadTexture(GameWindow::renderer, path); 
    // set the height and width of player based on the image height and width
    SDL_QueryTexture(player->image, NULL, NULL, &player->width, &player->height);
    Entities::curr_player = player;

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
    SDL_SetCursor(cursor);
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
    Player* player = Entities::curr_player;
    gun->xpos = player->xpos + 10;
    gun->ypos = player->ypos + 10;
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
    Player* player = Entities::curr_player;

    SDL_RenderClear(GameWindow::renderer);

    SDL_Rect player_rect;
    player_rect.x = player->xpos;
    player_rect.y = player->ypos;
    player_rect.h = player->height;
    player_rect.w = player->width;

   
    SDL_RenderCopy(GameWindow::renderer, player->image, NULL, &player_rect);   

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
    for (auto& e : Entities::enemies)
    {
        delete e;
    }
    SDL_DestroyTexture(Entities::curr_player->image);
    SDL_DestroyRenderer(GameWindow::renderer);
    SDL_DestroyWindow(GameWindow::window);
    SDL_FreeCursor(cursor);
    SDL_FreeSurface(cursor_surface);
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


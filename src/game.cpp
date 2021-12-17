#include "Keyboard.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Gun.hpp"
#include "Collision.hpp"
#include "Enemies.hpp"
#include "Enemy.hpp"
#include  <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameWindow.hpp"

bool Game::running = false;
SDL_Event Game::event;

int Player::width;
int Player::height;
bool Player::canshoot;
bool Player::canwalk;


SDL_Texture* Gun::image;
SDL_Texture* Gun::bullet_image;
int Gun::xpos;
int Gun::ypos;
int Gun::height;
int Gun::width;
float Gun::angle;
unsigned int Gun::max_ammo;
unsigned int Gun::ammo_per_shot;
int Gun::bullet_damage;



// debug stuff
float Game::last_speed;
float Game::last_y;
float Game::last_x;

int GameWindow::width;
int GameWindow::height;
SDL_Renderer* GameWindow::renderer;
SDL_Window* GameWindow::window;

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
    //Gun::xpos = Player::xpos + 20;
    //Gun::ypos = Player::ypos;
    Gun::ammo_per_shot = per_shot;
    Gun::max_ammo = ammo_max;
    Gun::image = IMG_LoadTexture(GameWindow::renderer, path);
    Gun::bullet_image = IMG_LoadTexture(GameWindow::renderer, path2);
    Gun::bullet_damage = dmg;
    // set the height and width of the gun and bullet based on the image height and width
    SDL_QueryTexture(Gun::image, NULL, NULL, &Gun::width, &Gun::height);

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

    Gun::xpos = Player::xpos + 10;
    Gun::ypos = Player::ypos + 10;
    Gun::angle = Game::get_degree(Gun::xpos, Gun::ypos, mouse_x, mouse_y);


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
    
    for (unsigned int i = 0; i < Enemy::enemies.size(); ++i)
    {
        auto* e = Enemy::enemies[i];
        //e->Move;

        SDL_Rect enemy_rect = entity_to_rect(e);
        // offset the x value so that guns appears near the player; not on top
        enemy_rect.x += 100;

         for (auto& b : Gun::bullets)
         {

                SDL_Rect bullet_rect = entity_to_rect(b);

            if(Collision::AABB(enemy_rect, bullet_rect))
            {
                   e->health -= b->damage;
            }
         }

            if (e->health < 1)
            {
                delete e;
                Enemy::enemies.erase(Enemy::enemies.begin()+i);
            }

    }
            

}

void Game::Draw()
{
    SDL_RenderClear(GameWindow::renderer);

    SDL_Rect player_rect;
    player_rect.x = Gun::xpos;
    player_rect.y = Gun::ypos;
    player_rect.h = Gun::height;
    player_rect.w = Gun::width;

   
    SDL_RenderCopy(GameWindow::renderer, Player::image, NULL, &player_rect);   

    SDL_Rect gun_rect;
    gun_rect.x = Gun::xpos;
    gun_rect.y = Gun::ypos;
    gun_rect.h = Gun::height;
    gun_rect.w = Gun::width;
    SDL_RenderCopyEx(GameWindow::renderer, Gun::image, NULL, &gun_rect, Gun::angle, NULL, SDL_FLIP_NONE);   

    for (auto& b : Gun::bullets)
    {
        SDL_Rect bull_rect;
        bull_rect.x = b->xpos;
        bull_rect.y = b->ypos;
        bull_rect.h = b->height;
        bull_rect.w = b->width;
        SDL_RenderCopyEx(GameWindow::renderer, b->image, NULL, &bull_rect, b->direction, NULL, SDL_FLIP_NONE);  
    }

    for (auto& e : Enemy::enemies)
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


void Game::HandleDebug()
{

    //bunch of messy code but no one will use this but me so who cares 
        
        printf("current X coordinate: %f \n", Player::xpos);
       
        printf("current Y coordinate: %f \n", Player::ypos);

        printf("current player speed: %f \n", Player::speed);

        printf("Player can shoot: %s \n", Player::canshoot ? "yes" : "no");

        printf("Player can walk: %s \n", Player::canwalk ? "yes" : "no");

        printf("Bullet Damage: %d \n", Gun::bullet_damage);

        printf("Bullets: %ld \n", Gun::bullets.size());
        printf("Enemies: %ld \n", Enemy::enemies.size());

        // clear the screen 
        printf("\033[H\033[2J\033[3J");
    
}


void Game::CreateEnemy(EnemyUtils::Enemies enemy_choice)
{
    Enemy* new_enemy = nullptr;
    new_enemy = new Basic_Shooter(100,100);
    
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
#include "Keyboard.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Gun.hpp"
#include "Collision.hpp"
#include "Enemies.hpp"
#include  <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool Game::running = false;
SDL_Event Game::event;
SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;

int Player::width;
int Player::height;
bool Player::canshoot;
bool Player::canwalk;


SDL_Texture* Gun::image;
SDL_Texture* Gun::bullet_image;
float Gun::xpos;
float Gun::ypos;
int Gun::height;
int Gun::width;
float Gun::angle;
unsigned int Gun::max_ammo;
unsigned int Gun::ammo_per_shot;



// debug stuff
float Game::last_speed;
float Game::last_y;
float Game::last_x;

void Game::CreatePlayer(float x, float y, float s, const char* path)
{
    Player::canwalk = true;
    Player::canshoot = true;
    Player::speed = s;
    Player::xpos = x;
    Player::ypos = y;
    Player::image = IMG_LoadTexture(renderer, path); 
    // set the height and width of player based on the image height and width
    SDL_QueryTexture(Player::image, NULL, NULL, &Player::width, &Player::height);

}

void Game::CreateGun(unsigned int per_shot, unsigned int ammo_max, const char* path, const char* path2)
{
    Gun::xpos = Player::xpos + 20;
    Gun::ypos = Player::ypos;
    Gun::ammo_per_shot = per_shot;
    Gun::max_ammo = ammo_max;
    Gun::image = IMG_LoadTexture(renderer, path);
    Gun::bullet_image = IMG_LoadTexture(renderer, path2);
    // set the height and width of the gun and bullet based on the image height and width
    SDL_QueryTexture(Gun::image, NULL, NULL, &Gun::width, &Gun::height);

}

bool Game::Running()
{
    return Game::running;
}

int Game::Window_Width;
int Game::Window_Height;
void Game::Start()
{   
    SDL_GetWindowSize(window, &Game::Window_Width, &Game::Window_Height); 
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


}

void Game::Draw()
{
    SDL_RenderClear(Game::renderer);

    SDL_Rect player_rect;

    player_rect.x = Player::xpos;
    player_rect.y = Player::ypos;
    player_rect.h = Player::height;
    player_rect.w = Player::width;
    SDL_RenderCopy(renderer, Player::image, NULL, &player_rect);   

    SDL_Rect gun_rect;
    gun_rect.x = Gun::xpos;
    gun_rect.y = Gun::ypos;
    gun_rect.h = Gun::height;
    gun_rect.w = Gun::width;
    SDL_RenderCopyEx(renderer, Gun::image, NULL, &gun_rect, Gun::angle, NULL, SDL_FLIP_NONE);   

    for (auto& b : Gun::bullets)
    {
        SDL_Rect bull_rect;
        bull_rect.x = b->xpos;
        bull_rect.y = b->ypos;
        bull_rect.h = b->height;
        bull_rect.w = b->width;
        SDL_RenderCopyEx(renderer, b->image, NULL, &bull_rect, b->direction, NULL, SDL_FLIP_NONE);  
    }


    SDL_RenderPresent(renderer);
    
}

void Game::Clean()
{
    for (auto& b : Gun::bullets)
    {
        delete b;
    }
    SDL_DestroyTexture(Player::image);
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(Game::window);
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

        printf("Bullets: %ld \n", Gun::bullets.size());

        // clear the screen 
        printf("\033[H\033[2J\033[3J");
    
}


void Game::CreateEnemy(Enemies enemy_choice)
{
    if (enemy_choice == Enemies::Basic_Shooter)
    {
        Basic_Shooter* new_enemy = new Basic_Shooter();
        Basic_Shooter::enemy_list.push_back(new_enemy);
    }
}
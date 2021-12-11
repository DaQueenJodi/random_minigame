#include "Keyboard.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include  <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool Game::running = false;
SDL_Event Game::event;
SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;

SDL_Rect Player::player_rect;
int Player::width;
int Player::height;
// debug stuff
float Game::last_speed;
float Game::last_y;
float Game::last_x;

void Game::CreatePlayer(float x, float y, float s, const char* path = "gfx/player.png")
{
    printf("%f", s);
    Player::speed = s;
      printf("%f", Player::speed);
    Player::xpos = x;
    Player::ypos = y;
    Player::image = IMG_LoadTexture(renderer, path); 
    // set the height and width of player based on the image height and width
    SDL_QueryTexture(Player::image, NULL, NULL, &Player::width, &Player::height);
}


bool Game::Running()
{
    return Game::running;
}

void Game::Start()
{
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
            default:
                break;
        }
    }
}

void Game::Update()
{
    SDL_RenderClear(Game::renderer);


    Player::player_rect.x = Player::xpos;
    Player::player_rect.y = Player::ypos;
    Player::player_rect.h = Player::height;
    Player::player_rect.w = Player::width;
    SDL_RenderCopy(renderer, Player::image, NULL, &Player::player_rect);   

    SDL_RenderPresent(renderer);
    
}

void Game::Clean()
{
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(Game::window);
    SDL_Quit();
}


void Game::HandleDebug()
{

    //bunch of messy code but no one will use this but me so who cares 
        Game::last_x = Player::xpos;
        
        printf("current X coordinate: %f \n", Player::xpos);

        Game::last_y = Player::ypos;
       
        printf("current Y coordinate: %f \n", Player::ypos);

        Game::last_speed = Player::speed;
       
        printf("current player speed: %f \n", Player::speed);

        // clear the screen 
        printf("\033[H\033[2J\033[3J");
    
}
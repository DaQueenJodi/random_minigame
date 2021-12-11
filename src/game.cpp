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

void Game::CreatePlayer(int x, int y, unsigned int s = 1, const char* path = "gfx/player.png")
{
    Player::speed = s;
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
    while (SDL_PollEvent(&Game::event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Game::running = false;
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
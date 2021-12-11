#include <SDL2/SDL.h>
#include <iostream>
#include "Game.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char** argv)
{
    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
       
    Game::window = SDL_CreateWindow( "Welp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    Game::renderer = SDL_CreateRenderer(Game::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Game::Start();
    }

    Game::CreatePlayer(50, 80, 1, "gfx/player.png");

    while (Game::Running())
    {
        Game::HandleEvents();
        Game::Update();
    }   
    Game::Clean();
    return 0;
}
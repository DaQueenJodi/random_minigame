#include <SDL2/SDL.h>
#include <iostream>
#include "Game.hpp"
#include "GameWindow.hpp"



int main(int argc, char** argv)
{
    bool debug = false;
    if (argv[1])
        debug = true;


    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
       
    GameWindow::window = SDL_CreateWindow( "Welp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    GameWindow::renderer = SDL_CreateRenderer(GameWindow::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Game::Start();
    }

    Game::CreatePlayer(50, 80, 1, "gfx/player.png");
    Game::CreateGun(0, 10, 5, "gfx/gun.png", "gfx/bullet.png");
    Game::CreateEnemy(EnemyUtils::EnemyType::Basic_Shooter);

    while (Game::Running())
    {
        if (debug)
            Game::HandleDebug();   
        Game::HandleEvents();
        Game::Update();
        Game::Draw();
    }
    Game::Clean();
    return 0;
}
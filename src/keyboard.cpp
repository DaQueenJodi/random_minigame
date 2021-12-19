#include "Keyboard.hpp"
#include "Player.hpp"
#include "Entities.hpp"
#include <SDL2/SDL.h>


void HandleKeyboard()
{
    auto keystate = SDL_GetKeyboardState(NULL);
    float s = Entities::curr_player->speed;
    if (keystate[SDL_SCANCODE_LSHIFT] | keystate[SDL_SCANCODE_RSHIFT])
    {
        Entities::curr_player->speed = s * 1.25f;
    }



    if (keystate[SDL_SCANCODE_W])
        Player::Up();
    if (keystate[SDL_SCANCODE_A])
        Player::Left();
    if (keystate[SDL_SCANCODE_S])
        Player::Down();
    if (keystate[SDL_SCANCODE_D])
        Player::Right();
    
    Entities::curr_player->speed = s;
    Player::CheckBounds();
}
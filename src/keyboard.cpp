#include "Keyboard.hpp"
#include "Player.hpp"
#include <SDL2/SDL.h>

void HandleKeyboard()
{
    auto keystate = SDL_GetKeyboardState(NULL);
    float s = Player::get_speed();
    if (keystate[SDL_SCANCODE_LSHIFT] | keystate[SDL_SCANCODE_RSHIFT])
    {
        Player::set_speed(s * 1.25f);
    }



    if (keystate[SDL_SCANCODE_W])
        Player::Up();
    if (keystate[SDL_SCANCODE_A])
        Player::Left();
    if (keystate[SDL_SCANCODE_S])
        Player::Down();
    if (keystate[SDL_SCANCODE_D])
        Player::Right();
    
    Player::set_speed(s);
}
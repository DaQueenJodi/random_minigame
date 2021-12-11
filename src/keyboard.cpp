#include "Keyboard.hpp"
#include "Player.hpp"
#include <SDL2/SDL.h>

void HandleKeyboard(SDL_Event event)
{
    switch (event.button)
    {
        case SDLK_w:
            Player::Up();
        case SDLK_a:
            Player::Left();
        case SDLK_s:
            Player::Down();
        case SDLK_d:
            Player::Right();
    }
}
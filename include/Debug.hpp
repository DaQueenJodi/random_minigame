#pragma once
#include "GameWindow.hpp"
#include "Entities.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Debug
{
    public:
        static SDL_Texture* hitbox; 
        static bool debug_enabled;
        static void display_hitboxes();
        static void display_text();
};
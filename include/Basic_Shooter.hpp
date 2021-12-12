#pragma once
#include "Enemy.hpp"
#include <SDL2/SDL_image.h>

class Basic_Shooter : private Enemy
{
    enum curr_state
    {
        walk,
        run,
        shoot
    };
    public:
       static std::vector<Basic_Shooter*> enemy_list;
        Basic_Shooter();
        void PewPew();

};
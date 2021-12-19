#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Gun.hpp"
#include "Player.hpp"
#include <vector>

class Entities
{
    public:
        static std::vector<Enemy*> enemies;
        static std::vector<Entity*> bullets;
        static Gun* curr_gun;
        static Player* curr_player;
};
#include "Enemy.hpp"

std::vector<Enemy*> Enemy::enemies;

int Enemy::get_health()
{
    return health;
}
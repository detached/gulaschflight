
#include "enemy.hpp"

Enemy::Enemy(int _x, int _y) {
  x = _x;
  y = _y;
}

void Enemy::Move() {

  y = y + 1;
}

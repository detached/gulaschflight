
#include "player.hpp"

Player::Player(int _x, int _y) {
  x = _x;
  y = _y;
}

void Player::Move(float accel_x, float accel_y) {

  int new_x = x;
  int new_y = y;

  if (accel_x > 1.0) {
    new_x = x + (int) accel_x;
  }

  if (accel_x < -1.0) {
    new_x = x + (int) accel_x;
  }

  if (new_x > 0 && new_x < MAX_X - SHAPE_W) {
    x = new_x;
  }

  if (accel_y > 1.0) {
    new_y = y - (int) accel_y;
  }

  if (accel_y < -1.0) {
    new_y = y - (int) accel_y;
  }

  if (new_y > 0 && new_y < MAX_Y - SHAPE_H) {
    y = new_y;
  }
}

Bullet Player::EmitBullet() {

  Bullet b;
  b.x = x + SHAPE_W / 2;
  b.y = y;
  b.m_x = 0;
  b.m_y = BULLET_SPEED;

  return b;
}

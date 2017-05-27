#pragma once

#include "api.hpp"

class Enemy {

  public:
    static const int SHAPE_SIZE = 64;
    static const int SHAPE_W = 13;
    static const int SHAPE_H = 13;
    int x;
    int y;
    
    Enemy(int _x, int _y);
    
    void Move();
    Bullet EmitBullet();

    Pixel shape[SHAPE_SIZE] = {
      {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}, {12, 0},
      {0, 1}, {13, 1},
      {0, 2}, {13, 2},
      {0, 3}, {4, 3}, {9, 3}, {13, 3},
      {0, 4}, {5, 4}, {8, 4}, {13, 4},
      {0, 5}, {3, 5}, {10, 5}, {13, 5},
      {0, 6}, {3, 6}, {4, 6}, {9, 6}, {10, 6}, {13, 6},
      {0, 7}, {13, 7},
      {0, 8}, {13, 8},
      {0, 9}, {9, 9}, {13, 9},
      {0, 10}, {8, 10}, {13, 10},
      {0, 11}, {4, 11}, {5, 11}, {6, 11}, {7, 11}, {13, 11},
      {0, 12}, {13, 12},
      {1, 13}, {2, 13}, {3, 13}, {4, 13}, {5, 13}, {6, 13}, {7, 13}, {8, 13}, {9, 13}, {10, 13}, {11, 13}, {12, 13}
    };
  private:
    static const int MAX_X = 128;
    static const int MAX_Y = 128;
    static const int BULLET_SPEED = -5;
};
